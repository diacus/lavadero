/*
 * sdbesclavo.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <esclavo.h>
#include <stdlib.h>

double *suma( double *col1, double *col2, unsigned int size ) {

	int i;
	double *res;

	res = (double *) calloc( size, sizeof(double) );

	for( i = 0; i < size; i++ )
		res[i] = col1[i] + col2[i];

	return res;
}

int esclavo_listen() {
	return 0;
}
