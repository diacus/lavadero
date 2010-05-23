/*
 * matriz.h
 *
 *  Created on: 23/05/2010
 *      Author: diacus
 */

#ifndef MATRIZ_H_
#define MATRIZ_H_

typedef struct mtz{
	unsigned int cols;
	unsigned int rens;
	double *coef;
} matriz;

/* matriz *matriz_new( unsigned int r, unsigned int c )
 *
 * Crea una matriz de r renglones por c columnas y devuelve
 * un apuntador a la matriz recién creada.
 */

matriz *matriz_new( unsigned int r, unsigned int c );

/* int matriz_getRen( double **ren, matriz *m, int R )
 *
 * Obtiene una copia del C-ésimo renglón de la matriz apuntada
 * por m, lo escribe un el espacio apuntado por *col y devuelve
 * un entero igual al tamaño de la columna.
 */

int matriz_getRen( double **ren, matriz *m, int R );

/* int matriz_setRen( double *col, matriz *m, int C )
 *
 */

int matriz_setRen( double *col, matriz *m, int C );

/* int matriz_delete( matriz *m )
 *
 * Libera el espacio de memoria ocupado por la matriz apuntada
 * por m.
 */

int matriz_delete( matriz *m );

#endif /* MATRIZ_H_ */
