/*
 * sdbesclavo.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <sdbproceso.h>
#include <sdblinda.h>
#include <esclavo.h>
#include <matriz.h>
#include <stdlib.h>
#include <stdio.h>

#include <constantes.h>

double *suma( double *col1, double *col2, unsigned int size ) {

	int i;
	double *res;

	res = (double *) calloc( size, sizeof(double) );

	for( i = 0; i < size; i++ )
		res[i] = col1[i] + col2[i];

	return res;
}

int esclavo_listen() {
	estado *edo = sdbproceso_estado();
	printf("Esclavo %d esperando instrucciones\n", edo->my_rank );

	if( edo->my_rank == 2 )
		ejecuta_suma(0);
	else if( edo->my_rank == 3 )
		ejecuta_suma(MATRIZCUT);

	printf( "%d: He terminado mi suma\n", edo->my_rank );
	return 0;
}

int ejecuta_suma( int shift ) {

	return 0;
}
