/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <sdbespacio.h>
#include <stdlib.h>

/* pendiente *sdbespacio_newpendiente()
 *
 * Función para crear un nuevo registro de solicitudes
 * pendientes.
 *
 * Devuelve un apuntador al registro recién creado.
 */

pendiente *sdbespacio_newpendiente() {
	pendiente *res = (pendiente *) malloc( sizeof(pendiente) );
	return res;
}

/* int sdbespacio_deletependiente( pendiente *p )
 *
 * Función para liberar el espacio de memoria donde se almacena
 * una solicitud pendiente.
 *
 * Devuelve un entero igual a cero en caso de éxito, y un entero
 * distinto de cero en caso de error.
 */

int sdbespacio_deletependiente( pendiente *p ) { free(p); return 0; }

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


/* unsigned int sdbespacio_atiendeGrab( char *key, unsigned int src )
 *
 * Rutina para atender la petición Grab de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

unsigned int sdbespacio_atiendeGrab( char *key, unsigned int src ) {

	thash *tabla, *pendientes;
	unsigned int size;
	void *data;
	tabla = sdbespacio_gethash();
	data = thash_read( tabla, &size, key );

	if( size ) {
		MPI_Send( &size, 1, MPI_INT, src, SIZE, MPI_COMM_WORLD );
		MPI_Send( data, size, MPI_CHAR, src, DATA, MPI_COMM_WORLD );
	} else {
		pendientes = sdbespacio_getpendientes();
	}

	return size;
}
