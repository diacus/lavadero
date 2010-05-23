/*
 * sdbesclavo.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <esclavo.h>
#include <stdlib.h>

int suma( int *col1, int *col2, unsigned int size ) {

	int i, *res;

	res = (int *) calloc( size, sizeof(int) );

	for( i = 0; i < size; i++ )
		res[i] = col1[i] + col2[i];

	return 0;
}
