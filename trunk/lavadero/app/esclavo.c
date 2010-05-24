/*
 * sdbesclavo.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <sdbproceso.h>
#include <sdblinda.h>
#include <esclavo.h>
#include <stdlib.h>
#include <stdio.h>

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
	return 0;
}
