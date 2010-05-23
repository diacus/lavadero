/*
 * sdblinda.c
 *
 *  Created on: 15/05/2010
 *      Author: diacus
 */

#include <sdblinda.h>
#include <sdbproceso.h>
#include <sdbespacio.h>
#include <sdbesclavo.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>


/* int sdblinda_start( int argc, char *argv[] )
 *
 * Función para inicializar el espacio de tuplas
 */

int sdblinda_start( int argc, char *argv[] ) {

	estado *edo;

	MPI_Init(&argc, &argv);
	edo = sdbproceso_estado();

	/* ¿Cuál es mi identificador de proceso? */
	MPI_Comm_rank(MPI_COMM_WORLD, &(edo->my_rank));
	/* ¿Cuántos proceso hay en el sistema? */

	MPI_Comm_size(MPI_COMM_WORLD, &(edo->num_procs));

	edo->tag = BEGIN;

	return 0;
}

/* int sdblinda_store( void *data, unsigned int size, const char *key )
 *
 * Función para almacenar los size bytes de datos apuntados por data, bajo
 * la clave key.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_store( void *data, unsigned int size, char *key ) {

	unsigned int bytes;
	char *message = sdbproceso_pack( &bytes, data, size, key);

	MPI_Send( message, bytes, MPI_CHAR, LINDA, STORE, MPI_COMM_WORLD );

	return 0;
}

/* int sdblinda_grab( void **data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función elimina los datos
 * del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca la cantidad de bytes
 * recibidos exitosamente.
 */

int sdblinda_grab( void **data, char *key ) {

	int nbytes;
	estado *edo = sdbproceso_estado();

	/*Solicitando el dato con clave key para escritura */
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, GRAB, MPI_COMM_WORLD );

	/* Preparando la recepción del mensaje */
	MPI_Probe( LINDA, DATA, MPI_COMM_WORLD, &(edo->status) );
	MPI_Get_count( &(edo->status) , MPI_INT, &nbytes );
	*data = calloc( nbytes, sizeof(char) );

	/* Recibiendo la tupla solicitada */
	MPI_Recv( *data, nbytes, MPI_CHAR, LINDA, DATA, MPI_COMM_WORLD, &(edo->status) );

	return nbytes;

}


/* int sdblinda_read( void **data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función es parecida a sdblinda_grab,
 * sólo que NO elimina los datos del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca la cantidad de bytes
 * recibidos exitosamente.
 */

int sdblinda_read( void **data, char *key ) {
	int nbytes;
	estado *edo = sdbproceso_estado();

	/*Solicitando el dato con clave key para lectura */
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, READ, MPI_COMM_WORLD );

	/* Preparando la recepción del mensaje */
	MPI_Probe( LINDA, DATA, MPI_COMM_WORLD, &(edo->status) );
	MPI_Get_count( &(edo->status) , MPI_INT, &nbytes );
	*data = calloc( nbytes, sizeof(char) );

	/* Recibiendo la tupla solicitada */
	MPI_Recv( *data, nbytes, MPI_CHAR, LINDA, DATA, MPI_COMM_WORLD, &(edo->status) );

	return nbytes;
}



/* int sdblinda_drop( const char *key )
 *
 * Función para eliminar los datos guardados bajo la clave key almacenados en el
 * espacio de tuplas. Una vez borrados los datos, no se recuperarán.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_drop( char *key ) {
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, DROP, MPI_COMM_WORLD );
	return 0;
}

/* int sdblinda_stop()
 *
 * Una vez terminada la aplicación, esta función destruye el espacio
 * de tuplas.
 */

int sdblinda_stop() {

	estado *edo = sdbproceso_estado();

	if ( SOYESPACIO(edo) ) {
		thash_delete( sdbespacio_gethash() );
		thash_delete( sdbespacio_getpendientes() );
	}

	MPI_Finalize();
	return 0;
}
