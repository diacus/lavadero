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

#define MATRIZ_ELEM( m, r, c ) *( m->coef + m->cols * r + c )

/** matriz *matriz_new( unsigned int r, unsigned int c )
 *
 * Crea una matriz de r renglones por c columnas y devuelve
 * un apuntador a la matriz recién creada.
 */

matriz *matriz_new( unsigned int r, unsigned int c );

/** int matriz_getRen( double **ren, matriz *m, int R )
 *
 * Obtiene una copia del R-ésimo renglón de la matriz apuntada
 * por m, lo escribe un el espacio apuntado por *ren y devuelve
 * un entero igual al tamaño de la columna.
 */

int matriz_getRen( double **ren, matriz *m, int R );

/** int matriz_setRen( double *ren, matriz *m, int R )
 *
 * Copia el vector apuntado por ren en el R-ésimo renglón
 * de la matríz apuntada por m.
 *
 * Devuelve 0 en caso de éxito.
 */

int matriz_setRen( double *ren, matriz *m, int R );

/** int matriz_getCol( double **col, matriz *m, int C )
 *
 * Obtiene una copia de la C-ésima columna de la matriz apuntada
 * por m, lo escribe un el espacio apuntado por *col y devuelve
 * un entero igual al tamaño de la columna.
 */

int matriz_getCol( double **col, matriz *m, int C );

/** int matriz_setCol( double *col, matriz *m, int C )
 *
 * Copia el vector apuntado por col en la C-ésima columna
 * de la matríz apuntada por m.
 *
 * Devuelve 0 en caso de éxito.
 */

int matriz_setCol( double *col, matriz *m, int C );

/** int matriz_fill( matriz *m )
 *
 * Llena los coeficientes de la matriz apuntada por m,
 * con valores aleatorios entre 0 y 99.
 */

int matriz_fill( matriz *m );

/** int matriz_print( matriz *m)
 *
 * Imprime en pantalla la matriz apuntada por m
 */

int matriz_print( matriz *m);

/** int matriz_delete( matriz *m )
 *
 * Libera el espacio de memoria ocupado por la matriz apuntada
 * por m.
 */

int matriz_delete( matriz *m );

/** void array_print( double *arr, unsigned int sz )
 *
 * Imprime en pantalla un vector *arr de tamaño sz
 */
void array_print( double *arr, unsigned int sz );

#endif /* MATRIZ_H_ */
