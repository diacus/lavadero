/*
 * maestro.c
 *
 *  Created on: 23/05/2010
 *      Author: diacus
 */

#include <maestro.h>
#include <stdio.h>
#include <stdlib.h>

/* int maestro_init_suma()
 *
 */

int maestro_init_suma() {

	char key[256] = "";
	int i, shift = 3;
	double *renA, *renB, *renC;
	matriz *mA, *mB, *mC;
	maestro_generaMatrices( &mA, &mB, 6, 6 );
	mC = matriz_new(6,6);

	printf("Matriz A\n");
	matriz_print(mA);

	printf("Matriz B\n");
	matriz_print(mB);

	for( i = 0; i < shift; i++) {

		matriz_getRen( &renA, mA, i );
		matriz_getRen( &renB, mB, i );

		sprintf( key, "RenglonA%d", i );
		sdblinda_store(renA, mA->cols * sizeof(double), key );
		key[0] = '\0';
		free(renA);

		sprintf( key, "B%dRenglon", i );
		sdblinda_store(renB, mB->cols * sizeof(double), key );
		key[0] = '\0';
		free(renB);
	}


	for( i = 0; i < shift; i++ ) {

		key[0] = '\0';
		sprintf( key, "resultadoC%d", i );
		sdblinda_grab( (void **) &renC, key );
		matriz_setRen( renC, mC, i );
		free(renC);

	}

	printf("Matriz C\n");
	matriz_print(mC);


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
