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

typedef struct fech{

	int dia;
	float mes;
	double anio;


} fecha;

int prueba_linda( int argc, char *argv[] ) {
	/*char *s1 = "PING";
	char *s2 = "PONG";
	char *s5 = "USAR DROP";
	char *s3, *s4;*/
	estado *edo = sdbproceso_estado();
	fecha actual;
	actual.dia=24;
	actual.anio=20.10;
	actual.mes=5.7;

	sdblinda_iniciar( argc, argv );

	if( SOYESPACIO(edo) ) {
		printf("Soy el espacio\n");
	}
	else {
		/*printf("soy %d, envie tupla de tamaño long = %d\n",edo->my_rank,strlen(s1));*/
		/* printf("Iniciando comunicación entre procesos\n"); */
	/*	if(edo->my_rank==1){

			sdblinda_meter( s1 , strlen(s1) + 1, "ida" );
			printf("soy: %d Envie %s\n", edo->my_rank, s1 );
			sdblinda_sacar( &s3, "vuelta" );
			printf("soy: %d Recibi %s\n", edo->my_rank, s3 );
			sdblinda_meter( s5 , strlen(s1) + 1, "borrar" );
			printf("soy: %d Envie %s\n", edo->my_rank, s5 );
			sdblinda_meter( &actual , sizeof(fecha), "fecha" );
			printf("soy: %d Envie fecha\n", edo->my_rank);
		}
		else{

			sdblinda_meter( s2 , strlen(s2) + 1, "vuelta" );
			printf("soy: %d Envie %s\n", edo->my_rank, s2 );
			sdblinda_leer( &s4, "ida" );
			printf("soy: %d Recibi %s\n", edo->my_rank, s4 );
			sdblinda_suprimir( "borrar" );
			printf("soy: %d Borre tupla con clave borrar\n", edo->my_rank);
			sdblinda_sacar( &hoy, "fecha" );
			printf("soy: %d Recibi fecha\n", edo->my_rank);
			printf("%d / %f / %lf \n", hoy->dia, hoy->mes, hoy->anio);

		}*/
	}

	sdblinda_detener();
	return 0;
}

