/*
 * prueba.c
 *
 *  Created on: 06/05/2010
 *      Author: diacus
 */
#include <stdio.h>
#include <prueba.h>
#include <string.h>

#include <sdbproceso.h>
#include <sdbespacio.h>
#include <sdblinda.h>
#include <maestro.h>
#include <esclavo.h>

#define WSIZE 10

#define CREA_ENTERO(a) \
	a = (int *) malloc(sizeof(int))

#define BORRA_ENTERO(a) \
	free(a)

struct registro{
	int numero;
	char palabra[10];
	double promedio;
};

int prueba( int argc, char *argv[] ) {

	estado *edo;

	sdblinda_start(argc, argv);

	edo = sdbproceso_estado();
	if( SOYESPACIO(edo) )
		sdbespacio_start();

	else if( edo->my_rank == 1 )
		maestro_init_suma();
	else
		esclavo_listen();

	sdblinda_stop();
	return 0;
}

/*int prueblista( int argc, char *argv[] ) {

	char clave[256] = "";
	int i, *item;
	lista *aux, *lis = NULL;

	srand( time(NULL) );

	for( i = 0; i < 100 ; i++ ) {
		sprintf( clave, "%d", rand() % 10000 );
		CREA_ENTERO(item); *item = rand() % 1000;
		printf( "Insertando el entero %d, con clave \"%s\"\n", *item, clave );
		lis = lista_insert( lis, lista_new( (void *) item, sizeof(int), clave ) );
		clave[0] = '\0';
	}

	for( aux = lis; aux; aux = aux->next )
		printf( "Elemento %d, con clave \"%s\"\n", *((int *) aux->info), aux->key );

	return 0;
}*/

/*int pruebahash( int argc, char *argv[] ) {

	int *numero, *solicitud;
	unsigned int tam;
	thash *tabla = thash_new(512);

	srand( time(NULL) );
	CREA_ENTERO(numero); *numero = rand() % 10000;
	printf( "Entero generado: %d\n", *numero );

	thash_insert( tabla, numero, sizeof(int), "dato" );

	solicitud = thash_read( tabla, &tam,  "dato" );

	printf("Valor recuperado: %d\n", *solicitud );

	BORRA_ENTERO(solicitud);

	thash_delete(tabla);

	return 0;
}*/

void printbit( char c, unsigned int bits ) {
	if( bits > 1 )
		printbit( c >> 1, bits - 1 );
	putchar( c % 2? '1' : '0' );
}



/*int pruebabit() {
	unsigned char c = 0x8F;
	printbit( c, 8 ); putchar('\n');
	ROTAR( c, 3 );
	printbit( c, 8 );

	return 0;
}*/

int pruebapack() {

	/*struct registro origen, destino;
	char *msg, *cad;
	unsigned int bytes;*/

	return 0;

}
