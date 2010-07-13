/*
 * sdblinda.c
 *
 *  Created on: 15/05/2010
 *      Author: diacus
 */

/**
 * @file
 * @author Giovanni Medrano <ryubba@gmail.com>
 * @author Diego Guzmán <dr.guzsant@gmail.com>
 *
 * @version 1.0
 *
 * @section Descripción
 *
 * Implementación de los nodos que llevan a cabo la tarea
 * de espacios de tuplas, se encargan de recibir y atender peticiones
 * para metar, sacar y leer tuplas.
 * 
 */

#include <stdio.h>
#include <sdblinda.h>
#include <sdbproceso.h>
#include <sdbespacio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>

/* variable global que indica que ocurrio una falla*/
int falla = 0;

/* variable global que indica el sitio al que se envian los datos */
int site = 0;


/** int sdblinda_iniciar( int argc, char *argv[] )
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

/*
 * MPI_Irecv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &request);
  if (timer (&request, &status) == 0)
 */

/**
 *
 * Función para almacenar los size bytes de datos apuntados por data, bajo
 * la clave key.
 *
 * @param *key Clave con la que se almacenará la tupla.
 * @parem  data Tupla que se va a almacenar.
 *
 * @return El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_meter( char *key, tupla data ) {

	estado *edo = sdbproceso_estado();
	/* nbytes almacenará el tamaño del mensaje a enviar */
	int nbytes = strlen( key ) + 1 + TUPLA_SIZE( data );
	char c = '\0';
	int flag=0, time=0, i, f = 0;

	/* Empaquetado del mensaje que se enviará al espacio de tuplas */
	if( !edo->message )
		DELETE_MESSAGE(edo->message);
	edo->message = sdbproceso_pack( key, data );

	for ( i = 0; i <= f ; i++ ){
		MPI_Send( edo->message, nbytes, MPI_CHAR, site, STORE, MPI_COMM_WORLD );
		MPI_Irecv( &c , 1, MPI_CHAR, site, ACK, MPI_COMM_WORLD, &(edo->request) );
		while ( !flag ){
			/* Do some work ... */
			MPI_Test(&(edo->request), &flag, &(edo->status));
			time ++;
			if ( time == TIEMPO1 ){
				MPI_Cancel( &(edo->request) );
				printf( "Soy %d: El espacio de principal de tuplas fallo\n", edo->my_rank );
				falla ++;
				f++;
				site = 1;
			}
		}
		flag = 0;
	}

	return 0;
}

/*
 * MPI_Irecv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &request);
  if (timer (&request, &status) == 0)
 */

/** 
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función elimina los datos
 * del espacio de tuplas.
 *
 * @param *key La clave de la tupla que se va a sacar del espacio.
 * @param  data Es el espacio de memoria donde se deposita la tupla recien retirada.
 *
 * @return El valor de retorno le notifica al programador acerca la cantidad de bytes
 * recibidos exitosamente.
 *
 */
int sdblinda_sacar( char *key, tupla data ) {

	estado *edo = sdbproceso_estado();
	int flag = 0, i, f = 0, time = 0;

	for ( i = 0; i <= f ; i++ ){
		MPI_Send( key, strlen(key) + 1, MPI_CHAR, site, GRAB, MPI_COMM_WORLD );
		MPI_Irecv( data , TUPLA_SIZE(data), MPI_BYTE, site, DATA, MPI_COMM_WORLD, &(edo->request) );
		while ( !flag ){
			/* Do some work ... */
			MPI_Test(&(edo->request), &flag, &(edo->status));
			time ++;
			if ( time == TIEMPO2 ){
				MPI_Cancel( &(edo->request) );
				printf( "Soy %d: El espacio de principal de tuplas fallo\n", edo->my_rank );
				falla ++;
				f++;
				site = 1;
			}
		}
		flag = 0;
	}

	return TUPLA_BYTES(data);

}

/**
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función es parecida a sdblinda_sacar,
 * sólo que NO elimina los datos del espacio de tuplas.
 *
 * @param *key La clave de la tupla que se va a leer del espacio.
 * @param  data Es el espacio de memoria donde se deposita la tupla recuperada.
 *
 * @return El valor de retorno le notifica al programador acerca la cantidad de bytes
 * recibidos exitosamente.
 */

int sdblinda_leer( char *key, tupla data ) {

	estado *edo = sdbproceso_estado();

	MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA0, READ, MPI_COMM_WORLD );
	MPI_Recv( data , TUPLA_SIZE(data), MPI_BYTE, LINDA0, DATA, MPI_COMM_WORLD, &(edo->status) );


	return TUPLA_BYTES(data);
}



/**
 *
 * Función para eliminar los datos guardados bajo la clave key almacenados en el
 * espacio de tuplas. Una vez borrados los datos, no se recuperarán.
 *
 * @param key La clave de la tupla que se quiere eliminar.
 *
 * @return El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_suprimir( char *key ) {

		MPI_Send( key, strlen(key) + 1, MPI_CHAR, LINDA0, DROP, MPI_COMM_WORLD );

	return 0;
}

/** int sdblinda_detener()
 *
 * Una vez terminada la aplicación, esta función destruye el espacio
 * de tuplas.
 */

int sdblinda_detener() {

	estado *edo = sdbproceso_estado();
	char c = '\0';
	int espacio;


	if( SOYMAESTRO(edo) )
		for ( espacio = 0; espacio < NSITES; espacio ++ )
			MPI_Send( &c, 1, MPI_CHAR, espacio, END, MPI_COMM_WORLD );

	else if( SOYESPACIO(edo) ){
		ght_finalize( sdbespacio_gethash() );
		ght_finalize( sdbespacio_getpendientes() );
	}


	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
