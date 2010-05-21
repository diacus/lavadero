/*
 * sdblinda.c
 *
 *  Created on: 15/05/2010
 *      Author: diacus
 */

#include <sdblinda.h>
#include <sdbproceso.h>
#include <sdbmaestro.h>
#include <sdbesclavo.h>
#include <mpi.h>


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

	edo->tag = INICIO;

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

int sdblinda_store( void *data, unsigned int size, const char *key ) {

	unsigned int bytes;
	char *message = sdbproceso_pack( &bytes, data, size, key );

	MPI_Send( message, bytes, MPI_CHAR, LINDA, ENVIA, MPI_COMM_WORLD );

	return 0;
}


/* int sdblinda_read( void **data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data. Es parecida a grab, sólo que en ésta
 * no se elimina la tupla del espacio.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_read( void *data, const char *key ) {
	unsigned int bytes;
	char *buffer;
	//envia la clave a LINDA
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, DAME, MPI_COMM_WORLD );
	//recibe de LINDA el tamaño (TALLA) a almacenar
	MPI_Recv( &bytes, sizeof(unsigned int), MPI_INT, LINDA, TALLA, MPI_COMM_WORLD );
	//reserva memoria para almacenar los datos
	*buffer = (char *) calloc( bytes, sizeof(char) );
	//recibe los datos de LINDA
	MPI_Recv(buffer, bytes, MPI_CHAR, LINDA, RETIRA, MPI_COMM_WORLD );
	//iguala las direcciones del buffer recibido y los datos
	data = buffer;
	return 0;
}

/* int sdblinda_grab( void **data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función elimina los datos
 * del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_grab( void *data, const char *key ) {
	unsigned int bytes;
	char *buffer;
	//envia la clave a LINDA
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, DAME, MPI_COMM_WORLD );
	//recibe de LINDA el tamaño (TALLA) a almacenar
	MPI_Recv( &bytes, sizeof(unsigned int), MPI_INT, LINDA, TALLA, MPI_COMM_WORLD );
	//reserva memoria para almacenar los datos
	*buffer = (char *) calloc( bytes, sizeof(char) );
	//recibe los datos de LINDA
	MPI_Recv(buffer, bytes, MPI_CHAR, LINDA, RETIRA, MPI_COMM_WORLD );
	//iguala las direcciones del buffer recibido y los datos
	data = buffer;
	//elimina la tupla con clave key
	sdblinda_drop( key );
	return 0;
}

/* int sdblinda_drop( const char *key )
 *
 * Función para eliminar los datos guardados bajo la clave key almacenados en el
 * espacio de tuplas. Una vez borrados los datos, no se recuperarán.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_drop( const char *key ) {
	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA, ELIMINA, MPI_COMM_WORLD );
	return 0;
}

/* int sdblinda_stop()
 *
 * Una vez terminada la aplicación, esta función destruye el espacio
 * de tuplas.
 */

int sdblinda_stop() {

	estado *edo = sdbproceso_estado();

	if ( SOYMAESTRO(edo) )
		thash_delete( sdbmaestro_gethash() );

	MPI_Finalize();
	return 0;
}
