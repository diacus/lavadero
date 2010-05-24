/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <sdbespacio.h>
#include <stdlib.h>

/* thash *sdbespacio_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbespacio_gethash() {
	static int creadaHash = 0;
	static thash *tabla = NULL;

	if( ! creadaHash ) {
		creadaHash ++;
		/* Esta parte puede ser parametrizada con */
		/* un archivo de configuración            */
		tabla = thash_new(TABLESIZE);
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
		creadaPendientes ++;
		/* Esta parte puede ser parametrizada con */
		/* un archivo de configuración            */
		pendientes = thash_new(TABLESIZE);
	}

	return pendientes;
}

/* int sdbmaestro_start()
 *
 * Función para inicializar el especio de tuplas.
 */

int sdbespacio_start() {

	/* thash *tabla = sdbespacio_gethash(); / * apuntador a tabla hash */
	estado *edo = sdbproceso_estado(); /* apuntador a estado (propio de LINDA) */
	char *buffer; /* buffer de mensaje a recibir */
	int n = edo -> num_procs - 1; /* número de procesos activos al momento de iniciar la comunicación */
	int nbytes;
	int source, tag; /* tamaño (nbytes) del buffer a recibir, identidad (source) del emisor y
	etiqueta (tag) del mensaje */


	printf("hay %d procesos \n", n);
	while( n > 0 ) {


		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &(edo->status));
		source = (edo->status).MPI_SOURCE;
		tag = (edo->status).MPI_TAG;
		MPI_Get_count(&(edo->status), MPI_BYTE, &nbytes);
		printf("bytes a recibir = %d\n", nbytes);
		buffer = (char *) calloc( nbytes, sizeof(char) );
		MPI_Recv( buffer, nbytes, MPI_BYTE, source, tag, MPI_COMM_WORLD, &(edo->status) );

		switch(tag){

		case END :
			printf("Recibi mensaje FIN de proc %d\n", source);
			n--;
			break;

		case STORE :
			printf("Recibi mensaje STORE de proc %d\n", source);
			sdbespacio_atiendeStore( buffer, nbytes );
			break;

		case GRAB :
			printf("Recibi mensaje GRAB de proc %d\n", source);
			/* int sdbespacio_atiendeGrab( char *key, unsigned int src )*/
			sdbespacio_atiendeGrab( buffer, source);
			break;

		case READ :
			printf("Recibi mensaje READ de proc %d\n", source);
			/* int sdbespacio_atiendeRead( char *key, unsigned int src ) */
			sdbespacio_atiendeRead( buffer, source );
			break;

		case DROP :
			printf("Recibi mensaje DROP de proc %d\n", source);
			/* int sdbespacio_atiendeDrop( char *key )*/
			/*sdb_espacio_atiendeDrop ( buffer );*/


		default:
			n=0;
			printf("Error de aplicación terminando\n");

		}

	}

	return 0;
}


/* unsigned int sdbespacio_atiendeStore( char * message, int sz )
 *
 * Función que recibe un mensaje y el tamaño en bytes de éste
 * almacena en la tabla hash la tupla contenida en el mensaje
 * empleando la clave también empaquetada en el mensaje
 *
 */
unsigned int sdbespacio_atiendeStore( char * message, int sz ){

	thash *tabla, *poratender; /* Creación de apuntador a la tabla hash de indices y tabla de pendientes*/
	pendiente *p; /* apuntador a la estructura pendiente */
	void * data; /* Tupla a almacenar */
	char *key;	/* Clave de la tupla */
	int indice, tam; /* índice de la tabla en el que se almacenará la tupla y tamaño de la tupla*/
	/* Proceso para desempaquetar la tupla se recibe el tamaño de la tupla*/
	tam = sdbproceso_unpack( message, sz, &key, &data);
	/* Se obtiene la dirección de la tabla hash */
	tabla = sdbespacio_gethash();
	/* se inserta en la tabla hash (tabla), el dato (data), de tamaño (tam) con clave (key)*/
	indice = thash_insert( tabla, data, tam, key);
	printf("Tupla insertada en el indice %d con clave %s\n", indice, key);

	/* Revisando el tabla de pendiente*/
	poratender = sdbespacio_getpendientes();

	/* void *thash_read( thash *t, unsigned int *sz, char *key ) */
	p = thash_remove( poratender, sizeof(pendiente), key);




	return 0;
}

/* int sdbespacio_atiendeGrab( char *key, unsigned int src )
 *
 * Rutina para atender la petición Grab de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeGrab( char *key, unsigned int src ) {

	thash *tabla, *poratender;
	pendiente *p;
	unsigned int size;
	void *data;

	tabla = sdbespacio_gethash();
	data = thash_remove( tabla, &size, key );

	if( size ) {
		MPI_Send( data, size, MPI_CHAR, src, DATA, MPI_COMM_WORLD );
		free(data);
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

/* int sdbespacio_atiendeRead( char *key, unsigned int src )
 *
 * Rutina para atender la petición Read de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeRead( char *key, unsigned int src ) {

	thash *tabla, *poratender;
	pendiente *p;
	unsigned int size;
	void *data;

	tabla = sdbespacio_gethash();
	data = thash_read( tabla, &size, key );

	if( size ) {
		MPI_Send( data, size, MPI_CHAR, src, DATA, MPI_COMM_WORLD );
		free(data);
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

/* int sdbespacio_atiendeDrop( char *key )
 *
 * Rutina para atender la petición Drop.
 */

int sdbespacio_atiendeDrop( char *key ) {

	thash *tabla = sdbespacio_gethash();
	unsigned int size;
	void *data;

	data = thash_remove( tabla, &size, key );

	if( size )
		free(data);

	return 0;
}

