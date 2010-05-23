/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

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

/* int sdbespacio_start()
 *
 * Función para inicializar el especio de tuplas.
 */

int sdbespacio_start() {

	/* thash *tabla = sdbespacio_gethash();*/
	estado *edo = sdbproceso_estado();
	/* char *message; */

	while( edo->tag != END ) {

	}

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

