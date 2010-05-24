/*
 * maestro.c
 *
 *  Created on: 23/05/2010
 *      Author: diacus
 */

#include <maestro.h>

/* int maestro_init_suma()
 *
 */

int maestro_init_suma() {

	matriz *mA, *mB;
	maestro_generaMatrices( &mA, &mB, 5, 5 );
	return 0;
}

/* int maestro_generaMatrices( matriz **A, matriz **B, int r, int c )
 *
 */

int maestro_generaMatrices( matriz **A, matriz **B, int r, int c ) {

	*A = matriz_new(r,c);
	*B = matriz_new(r,c);

	matriz_fill(*A);
	matriz_fill(*B);

	return 0;
}
