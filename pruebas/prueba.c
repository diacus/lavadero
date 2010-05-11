/*
 * prueba.c
 *
 *  Created on: 06/05/2010
 *      Author: diacus
 */
#include <stdio.h>
#include <prueba.h>
#include <thash.h>

int prueba1() {

	/* probando singleton */
	thash h1, h2;

	h1 = thash_get();

	h1[0] = 1986;

	h2 = thash_get();

	printf("%d\n", h2[0] );

	return 0;
}

int pruebahash( int argc, char *argv[] ) {
	return 0;
}
