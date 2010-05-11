/*
 * prueba.c
 *
 *  Created on: 06/05/2010
 *      Author: diacus
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <prueba.h>
#include <string.h>
#include <thash.h>
#include <lista.h>

#define CREA_ENTERO(a) \
	a = (int *) malloc(sizeof(int));

#define BORRA_ENTERO(a) \
	free(a);

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

	char clave[256] = "";
	int i, *item;
	srand( time(NULL) );

	CREA_ENTERO(item); *item = rand() % 1000;
	lista *lis = lista_new( (void *) item, "inicio" );

	for( i = 0; i < 10 ; i++ ) {
		sprintf( clave, "item%02d", i);
		CREA_ENTERO(item); *item = rand() % 1000;
		lista_insert( lis, lista_new( (void *) item, clave ) );
		clave[0] = '\0';
	}

	return 0;
}
