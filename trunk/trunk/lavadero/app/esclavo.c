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

	if( edo->my_rank == 2 )
		ejecuta_suma(0);
	else if( edo->my_rank == 3 )
		ejecuta_suma(3);

	printf( "%d: He terminado mi suma\n", edo->my_rank );
	return 0;
}

int ejecuta_suma( int shift ) {

	char key[256] = "";
	double *renA, *renB, *renC;
	int i, size, lim = shift + 3;

	estado *edo = sdbproceso_estado();

	for( i = shift; i < lim ; i++ ) {

		sprintf( key, "RenglonA%d", i );
		size = sdblinda_read( (void **) &renA, key );
		key[0] = '\0';

		sprintf( key, "B%dRenglon", i );
		sdblinda_read( (void **) &renB, key );
		key[0] = '\0';

		renC = suma( renA, renB, size / sizeof(double) );

		sprintf( key, "resultadoC%d", i );
		sdblinda_store( renC, size, key );
		key[0] = '\0';

		printf("%d: Renglon %dA ", edo->my_rank, i );
		array_print(renA, size / sizeof(double) );

		printf("%d: Renglon %dB ", edo->my_rank, i );
		array_print(renB, size / sizeof(double) );

		printf("%d: Renglon %dC ", edo->my_rank, i );
		array_print(renC, size / sizeof(double) );

		free(renA); free(renB); free(renC);

	}

	return 0;

}

void array_print( double *arr, unsigned int sz ) {
	double *ini, *fin;
	fin = arr + sz;
	for( ini = arr; ini < fin; ini++ )
		printf("% .3f", *ini);
	putchar('\n');
}
