/*
 * pruebaLinda.c
 *
 *  Created on: 18/05/2010
 *      Author: diacus
 */

#include <prueba.h>
#include <sdbproceso.h>
#include <sdblinda.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*int listen() {
	int n;
	estado *edo = sdbproceso_estado();

	n = edo->num_procs - 1;

	while( n > 0 ) {
		MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &(edo->status) );

		switch( edo->status.MPI_TAG ) {
		case STORE:
			break;
		case READ:
			break;
		case GRAB:
			break;
		case DROP:
			break;
		}

	}

	return 0;
}*/


int prueba_linda( int argc, char *argv[] ) {
	char *s1 = "PING";
	char *s2 = "PONG";
	char *s5 = "USAR DROP";
	char *s3, *s4;
	estado *edo = sdbproceso_estado();
	sdblinda_start( argc, argv );

	if( SOYESPACIO(edo) ) {
		printf("Soy el espacio\n");
	}
	else {
		/*printf("soy %d, envie tupla de tamaño long = %d\n",edo->my_rank,strlen(s1));*/
		/* printf("Iniciando comunicación entre procesos\n"); */
		if(edo->my_rank==1){

			sdblinda_store( s1 , strlen(s1) + 1, "ida" );
			printf("soy: %d Envie %s\n", edo->my_rank, s1 );
			sdblinda_grab( &s3, "vuelta" );
			printf("soy: %d Recibi %s\n", edo->my_rank, s3 );
			sdblinda_store( s5 , strlen(s1) + 1, "borrar" );
			printf("soy: %d Envie %s\n", edo->my_rank, s5 );
		}
		else{

			sdblinda_store( s2 , strlen(s2) + 1, "vuelta" );
			printf("soy: %d Envie %s\n", edo->my_rank, s2 );
			sdblinda_read( &s4, "ida" );
			printf("soy: %d Recibi %s\n", edo->my_rank, s4 );
			sdblinda_drop( "borrar" );
			printf("soy: %d Borre tupla con clave borrar\n", edo->my_rank);

		}
	}

	sdblinda_stop();
	return 0;
}

