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
#include <thash.h>


/* thash *sdbespacio_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbespacio_gethash() {

	static int creadaHash = 0;
	static thash *tabla = NULL;

	if( ! creadaHash ) {
		creadaHash ++;                	/* Esta parte puede ser parametrizada con */
		tabla = thash_new(TABLESIZE);	/* un archivo de configuración            */
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
		creadaPendientes ++;               	/* Esta parte puede ser parametrizada con */
		pendientes = thash_new(TABLESIZE);	/* un archivo de configuración            */
	}

	return pendientes;
}

/* int sdbmaestro_iniciar()
 *
 * Función para inicializar el especio de tuplas.
 */

int sdbespacio_iniciar() {
	thash  *tabla   = sdbespacio_gethash();	/* Apuntador a tabla hash 																			*/
	estado *edo     = sdbproceso_estado();	/* Apuntador a estado (propio de LINDA)																*/
	char   *buffer;							/* Buffer de mensaje a recibir																		*/
	int     nbytes, source, tag;			/* Tamaño (nbytes) del buffer a recibir, identidad (source) del emisor y etiqueta (tag) del mensaje */
	int error = 0;

	while( edo->tag != END ) {
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &(edo->status));
		source = (edo->status).MPI_SOURCE;
		tag = (edo->status).MPI_TAG;
		MPI_Get_count(&(edo->status), MPI_BYTE, &nbytes);
		buffer = (char *) calloc( nbytes, sizeof(char) );
		MPI_Recv( buffer, nbytes, MPI_BYTE, source, tag, MPI_COMM_WORLD, &(edo->status) );
		switch(tag) {
		case END :
			edo->tag = END;
			break;
		case STORE :
			sdbespacio_atiendeMeter( buffer, nbytes, tabla );
			break;
		case GRAB :
			sdbespacio_atiendeSacar( buffer, source, tabla);
			break;
		case READ :
			sdbespacio_atiendeLeer( buffer, source, tabla );
			break;
		case DROP :
			sdbespacio_atiendeSuprimir ( buffer, tabla );
			break;
		default:
			fprintf( stderr, "Error de aplicación\n" );
			error++;
		}
		DELETE_MESSAGE(buffer);
	}
	return error;
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
	tupla         data;			/* Tupla a almacenar                                                        */
	char         *key;			/* Clave de la tupla                                                        */
	int           indice, tam;	/* índice de la tabla en el que se almacenará la tupla y tamaño de la tupla */
	int error = 0;

	poratender = sdbespacio_getpendientes();
	tam    = sdbproceso_unpack( message, sz, &key, &data);

	indice = thash_insert(tabla, data, key );
	p = thash_remove( poratender, key );

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
		error++;
	}

	return error;
}

/* int sdbespacio_atiendeSacar( char *key, unsigned int src )
 *
 * Rutina para atender la petición Sacar de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeSacar( char *key, unsigned int src, thash *tabla ) {

	int error = 0;
	thash 		 *poratender;
	pendiente	 *p;
	tupla		 *data;

	data = thash_remove( tabla, key );

	if( data ) {
		MPI_Send( data, TUPLA_SIZE(data), MPI_CHAR, src, DATA, MPI_COMM_WORLD );
		DELETE_MESSAGE(data);
	} else {
		poratender = sdbespacio_getpendientes();
		NEWPENDIENTE(p);
		p->key = strdup(key);
		p->cliente = src;
		p->op = GRAB;

		thash_insert(poratender, p, key );
		error++;
	}

	return error;
}

/* int sdbespacio_atiendeLeer( char *key, unsigned int src )
 *
 * Rutina para atender la petición Leer de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeLeer( char *key, unsigned int src, thash *tabla ) {

	int error = 0;
	thash *poratender;
	pendiente *p;
	tupla data;

	data = thash_read( tabla, key );

	if( data )
		MPI_Send( data, TUPLA_SIZE(data), MPI_CHAR, src, DATA, MPI_COMM_WORLD );
	else {
		poratender = sdbespacio_getpendientes();
		NEWPENDIENTE(p);
		p->key     = strdup(key);
		p->cliente = src;
		p->op      = READ;
		thash_insert(poratender, p, key );
		error++;
	}

	return error;
}

/* int sdbespacio_atiendeSuprimir( char *key )
 *
 * Rutina para atender la petición Suprimir.
 */

int sdbespacio_atiendeSuprimir( char *key, thash *tabla ) {

	int error = 0;
	tupla *data;

	data = thash_remove( tabla, key );

	if( data )
		DELETE_MESSAGE(data)
	else
		error++;

	return error;
}
