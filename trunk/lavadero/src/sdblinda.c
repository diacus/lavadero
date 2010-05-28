/*
 * sdblinda.c
 *
 *  Created on: 15/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <sdblinda.h>
#include <sdbproceso.h>
#include <sdbespacio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>


/* int sdblinda_iniciar( int argc, char *argv[] )
 *
 * Función para inicializar el espacio de tuplas
 */

int sdblinda_iniciar( int argc, char *argv[] ) {

	estado *edo;

	MPI_Init(&argc, &argv);
	edo = sdbproceso_estado();

	/* ¿Cuál es mi identificador de proceso? */
	MPI_Comm_rank(MPI_COMM_WORLD, &(edo->my_rank));
	/* ¿Cuántos proceso hay en el sistema? */

	MPI_Comm_size(MPI_COMM_WORLD, &(edo->num_procs));

	edo->tag = BEGIN;

	/*arranque del espacio de tuplas para atención de peticiones*/
	if (SOYESPACIO(edo)){
		printf("Iniciando Espacio de Tuplas\n");
		sdbespacio_iniciar();
	}

	return 0;
}


/* int sdblinda_meter( void *data, unsigned int size, const char *key )
 *
 * Función para almacenar los size bytes de datos apuntados por data, bajo
 * la clave key.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_meter( char *key, tupla data ) {

	estado *edo = sdbproceso_estado();
	/* nbytes almacenará el tamaño del mensaje a enviar */
	int nbytes = strlen(key) + 1 + TUPLA_SIZE(data);

	/* Empaquetado del mensaje que se enviará al espacio de tuplas */
	if( !edo->message )
		DELETE_MESSAGE(edo->message);
	edo->message = sdbproceso_pack( key, data );

	/* Envia a LINDA el mensaje (message) de tamaño nbytes para almacenarlo (STORE)*/
	MPI_Send( edo->message, nbytes, MPI_CHAR, LINDA, STORE, MPI_COMM_WORLD );

	return 0;
}

/* int sdblinda_sacar( void **data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función elimina los datos
 * del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca la cantidad de bytes
 * recibidos exitosamente.
 */

int sdblinda_sacar( tupla data, char *key ) {

	estado *edo = sdbproceso_estado();

	/* Solicitando el dato con clave key para escritura */
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, GRAB, MPI_COMM_WORLD );

	/* Recibiendo la tupla solicitada */
	MPI_Recv( TUPLA_INFO(data), TUPLA_BYTES(data), MPI_BYTE, LINDA, DATA, MPI_COMM_WORLD, &(edo->status) );

	return TUPLA_BYTES(data);

}

/* int sdblinda_leer( void **data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función es parecida a sdblinda_sacar,
 * sólo que NO elimina los datos del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca la cantidad de bytes
 * recibidos exitosamente.
 */

int sdblinda_leer( char *key, tupla data ) {

	estado *edo = sdbproceso_estado();

	/*Solicitando el dato con clave key para lectura */
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, READ, MPI_COMM_WORLD );

	/* Recibiendo la tupla solicitada */
	MPI_Recv( TUPLA_INFO(data),
			  TUPLA_BYTES(data),
			  MPI_CHAR,
			  LINDA,
			  DATA,
			  MPI_COMM_WORLD,
			  &(edo->status)
			);

	return TUPLA_BYTES(data);
}



/* int sdblinda_suprimir( const char *key )
 *
 * Función para eliminar los datos guardados bajo la clave key almacenados en el
 * espacio de tuplas. Una vez borrados los datos, no se recuperarán.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_suprimir( char *key ) {
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, DROP, MPI_COMM_WORLD );
	return 0;
}

/* int sdblinda_detener()
 *
 * Una vez terminada la aplicación, esta función destruye el espacio
 * de tuplas.
 */

int sdblinda_detener() {

	estado *edo = sdbproceso_estado();
	char c = '\0';

	if( SOYMAESTRO(edo) )
		MPI_Send( &c, 1, MPI_CHAR, LINDA, END, MPI_COMM_WORLD );

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
