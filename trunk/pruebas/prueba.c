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

#define WSIZE 10

#define CREA_ENTERO(a) \
	a = (int *) malloc(sizeof(int))

#define BORRA_ENTERO(a) \
	free(a)


int prueba1() {

	return 0;
}

int prueblista( int argc, char *argv[] ) {

	char clave[256] = "";
	int i, *item;
	lista *aux, *lis = NULL;

	srand( time(NULL) );

	for( i = 0; i < 100 ; i++ ) {
		sprintf( clave, "%d", rand() % 10000 );
		CREA_ENTERO(item); *item = rand() % 1000;
		printf( "Insertando el entero %d, con clave \"%s\"\n", *item, clave );
		lis = lista_insert( lis, lista_new( (void *) item, clave ) );
		clave[0] = '\0';
	}

	for( aux = lis; aux; aux = aux->next )
		printf( "Elemento %d, con clave \"%s\"\n", *((int *) aux->info), aux->key );

	return 0;
}

int pruebahash( int argc, char *argv[] ) {

	int *numero, *solicitud;
	thash *tabla = thash_new(512);

	CREA_ENTERO(numero); *numero = rand() % 10000;
	printf( "Entero generado: %d\n", *numero );

	thash_insert( tabla, numero, "dato" );

	solicitud = thash_read( tabla, "dato" );

	printf("Valor recuperado: %d\n", *solicitud );

	BORRA_ENTERO(solicitud);

	thash_delete(tabla);

	return 0;
}

void printbit( char c, unsigned int bits ) {
	if( bits > 1 )
		printbit( c >> 1, bits - 1 );
	putchar( c % 2? '1' : '0' );
}



int pruebabit() {
	unsigned char c = 0x8F;
	printbit( c, 8 ); putchar('\n');
	ROTAR( c, 3 );
	printbit( c, 8 );

	return 0;
}
