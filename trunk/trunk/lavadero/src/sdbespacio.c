/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <stdlib.h>
#include <pendiente.h>
#include <sdbproceso.h>
#include <sdbespacio.h>


/* thash *sdbespacio_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbespacio_gethash() {

	static int creadaHash = 0;
	static thash *tabla = NULL;

	if( ! creadaHash ) {
		creadaHash ++;                /* Esta parte puede ser parametrizada con */
		tabla = thash_new(TABLESIZE); /* un archivo de configuración            */
	}

	return tabla;
}


/* thash *sdbespacio_getpendientes()
 *
 * Funcipon para obtener una referencia al espacio en el que
 * se van a almacenar las peticiones pendientes.
 */

thash *sdbespacio_getpendientes() {

	static int creadaPendientes = 0;
	static thash *pendientes = NULL;


	if( ! creadaPendientes ) {
		creadaPendientes ++;               /* Esta parte puede ser parametrizada con */
		pendientes = thash_new(TABLESIZE); /* un archivo de configuración            */
	}

	return pendientes;
}

/* void sdbmaestro_iniciar()
 *
 * Función para inicializar el especio de tuplas.
 */

void sdbespacio_iniciar() {
	thash  *tabla   = sdbespacio_gethash();	/* Apuntador a tabla hash */
	estado *edo     = sdbproceso_estado();	/* Apuntador a estado (propio de LINDA) */
	char   *buffer;							/* Buffer de mensaje a recibir */
	int     nbytes, source, tag;			/* Tamaño (nbytes) del buffer a recibir, identidad (source) del emisor y etiqueta (tag) del mensaje */

	while( edo->tag != END ) {
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &(edo->status));
		source = (edo->status).MPI_SOURCE;
		tag = (edo->status).MPI_TAG;
		MPI_Get_count(&(edo->status), MPI_BYTE, &nbytes);
		buffer = (char *) calloc( nbytes, sizeof(char) );
		MPI_Recv( buffer, nbytes, MPI_BYTE, source, tag, MPI_COMM_WORLD, &(edo->status) );
		switch(tag) {
		case END :
			printf( "SERVER: Recibi mensaje de END\n", nbytes, source );
			edo->tag = END;
			break;
		case STORE :
			printf( "SERVER: Recibi %d bytes de %d para meter\n", nbytes, source );
			sdbespacio_atiendeMeter( buffer, nbytes, tabla );
			break;
		case GRAB :
			printf( "SERVER: Recibi %d bytes de %d para sacar\n", nbytes, source );
			sdbespacio_atiendeSacar( buffer, source, tabla);
			break;
		case READ :
			printf( "SERVER: Recibi %d bytes de %d para leer\n", nbytes, source );
			sdbespacio_atiendeLeer( buffer, source, tabla );
			break;
		case DROP :
			sdbespacio_atiendeSuprimir ( buffer, tabla );
			break;
		default:
			fprintf( stderr, "Error de aplicación\n" );
		}
	}
}


/* unsigned int sdbespacio_atiendeMeter( char * message, int sz )
 *
 * Función que recibe un mensaje y el tamaño en bytes de éste
 * almacena en la tabla hash la tupla contenida en el mensaje
 * empleando la clave también empaquetada en el mensaje
 *
 */
unsigned int sdbespacio_atiendeMeter( char *message, int sz, thash *tabla ){

	thash        *poratender;	/* Creación de apuntador a la tabla hash de indices y tabla de pendientes   */
	pendiente    *p;			/* apuntador a la estructura pendiente                                      */
	void         *data;			/* Tupla a almacenar                                                        */
	char         *key;			/* Clave de la tupla                                                        */
	int           indice, tam;	/* índice de la tabla en el que se almacenará la tupla y tamaño de la tupla */
	unsigned int  size;

	tam    = sdbproceso_unpack( message, sz, &key, &data);
	indice = thash_insert( tabla, data, tam, key);

	poratender = sdbespacio_getpendientes();
	p = thash_remove( poratender, &size, key);

	if( p ) {
		switch( p->op ) {

			case GRAB :
				sdbespacio_atiendeSacar( key, p->cliente, tabla );
				break;

			case READ :
				sdbespacio_atiendeLeer( key, p->cliente, tabla );
				break;
		}

		DELETEPENDIENTE(p);
	}

	return 0;
}

/* int sdbespacio_atiendeSacar( char *key, unsigned int src )
 *
 * Rutina para atender la petición Sacar de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeSacar( char *key, unsigned int src, thash *tabla ) {

	thash 		 *poratender;
	pendiente	 *p;
	unsigned int  size;
	void		 *data;

	data = thash_remove( tabla, &size, key );

	if( size ) {
		MPI_Send( data, size, MPI_CHAR, src, DATA, MPI_COMM_WORLD );
		DELETE_MESSAGE(data);
	} else {
		poratender = sdbespacio_getpendientes();
		NEWPENDIENTE(p);
		p->key = strdup(key);
		p->cliente = src;
		p->op = GRAB;
		thash_insert(poratender, p, sizeof(pendiente), key );
	}

	return 0;
}

/* int sdbespacio_atiendeLeer( char *key, unsigned int src )
 *
 * Rutina para atender la petición Leer de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeLeer( char *key, unsigned int src, thash *tabla ) {

	thash *poratender;
	pendiente *p;
	unsigned int size;
	void *data;

	data = thash_read( tabla, &size, key );

	if( size ) {
		MPI_Send( data, size, MPI_CHAR, src, DATA, MPI_COMM_WORLD );
		DELETE_MESSAGE(data);
	} else {
		poratender = sdbespacio_getpendientes();
		NEWPENDIENTE(p);
		p->key = strdup(key);
		p->cliente = src;
		p->op = READ;
		thash_insert(poratender, p, sizeof(pendiente), key );
	}

	return 0;
}

/* int sdbespacio_atiendeSuprimir( char *key )
 *
 * Rutina para atender la petición Suprimir.
 */

int sdbespacio_atiendeSuprimir( char *key, thash *tabla ) {

	unsigned int size;
	void *data;

	data = thash_remove( tabla, &size, key );

	if( size )
		DELETE_MESSAGE(data)
	else
		fprintf( stderr, "SERVER: Operacion de borrado fallida, no se encontro la tupla\n");

	return 0;
}
