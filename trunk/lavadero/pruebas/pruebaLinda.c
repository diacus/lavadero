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
	char *s1 = "saludo";
	estado *edo = sdbproceso_estado();
	sdblinda_start( argc, argv );

	if( SOYESPACIO(edo) ) {
		printf("Soy el espacio\n");
	}
	else {
		printf("soy %d, long = %d\n",edo->my_rank,strlen(s1)+1);
		if(edo->my_rank==1)
			sdblinda_store(s1 , strlen(s1) + 1, "HELLO" );
		else
			sdblinda_store(s1 , strlen(s1) + 1, "HOLA" );
	}

	sdblinda_stop();
	return 0;
}

