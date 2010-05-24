/*
 * matriz.c
 *
 *  Created on: 23/05/2010
 *      Author: diacus
 */

#include <matriz.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* matriz *matriz_new( unsigned int r, unsigned int c )
 *
 * Crea una matriz de r renglones por c columnas y devuelve
 * un apuntador a la matriz recién creada.
 */

matriz *matriz_new( unsigned int r, unsigned int c ) {
	matriz *res;

	res = (matriz *) malloc( sizeof (matriz) );

	res->coef = (double *) calloc( r * c, sizeof(double) );
	res->cols = c; res->rens = r;

	return res;
}

/* int matriz_getRen( double **ren, matriz *m, int R )
 *
 * Obtiene una copia del R-ésimo renglón de la matriz apuntada
 * por m, lo escribe un el espacio apuntado por *ren y devuelve
 * un entero igual al tamaño de la columna.
 */

int matriz_getRen( double **ren, matriz *m, int R ) {

	*ren = (double *) calloc( m->cols, sizeof(double) );
	memcpy( *ren, (m->coef + m->cols * m->rens), m->cols * sizeof(double) );
	return 0;
}

/* int matriz_setRen( double *ren, matriz *m, int R )
 *
 * Copia el vector apuntado por ren en el R-ésimo renglón
 * de la matríz apuntada por m.
 *
 * Devuelve 0 en caso de éxito.
 */

int matriz_setRen( double *ren, matriz *m, int R ) {
	memcpy( m->coef + (m->cols * R), ren, m->cols * sizeof(double) );
	return 0;
}

/* int matriz_getCol( double **col, matriz *m, int C )
 *
 * Obtiene una copia de la C-ésima columna de la matriz apuntada
 * por m, lo escribe un el espacio apuntado por *col y devuelve
 * un entero igual al tamaño de la columna.
 */

int matriz_getCol( double **col, matriz *m, int C ) {
	int i;
	*col = (double *) calloc( m->rens, sizeof(double) );

	for( i = 0; i < m->rens; i++ )
		(*col)[i] = MATRIZ_ELEM( m, i, C );

	return 0;
}

/* int matriz_setCol( double *col, matriz *m, int C )
 *
 * Copia el vector apuntado por col en la C-ésima columna
 * de la matríz apuntada por m.
 *
 * Devuelve 0 en caso de éxito.
 */

int matriz_setCol( double *col, matriz *m, int C ) {
	int i;

	for( i = 0; i < m->rens; i++ )
		MATRIZ_ELEM( m, i, C ) = *(col + i);

	return 0;
}


/* int matriz_fill( matriz *m )
 *
 * Llena los coeficientes de la matriz apuntada por m,
 * con valores aleatorios entre 0 y 99.
 */

int matriz_fill( matriz *m ) {

	double *ini, *fin, *dob;

	srand( time(NULL) );
	ini = m->coef;
	fin = ini + (m->rens *m->cols);

	for( dob = ini; dob < fin; dob++ )
		*dob = rand() % 100;

	return 0;
}

/* int matriz_print( matriz *m)
 *
 * Imprime en pantalla la matriz apuntada por m
 */

int matriz_print( matriz *m) {
	int i, lim = m->cols * m->rens;

	for( i = 0; i < lim; i++ ) {
		if( i % m->cols == 0)
			putchar('\n');
		printf(" %.03f", *(m->coef + i) );
	}
	putchar('\n');
	return 0;
}

/* int matriz_delete( matriz *m )
 *
 * Libera el espacio de memoria ocupado por la matriz apuntada
 * por m.
 */

int matriz_delete( matriz *m ) {
	free( m->coef );
	free( m );
	return 0;
}
