/*
 * prueba.c
 *
 *  Created on: 06/05/2010
 *      Author: diacus
 */
#include <prueba.h>
#include <string.h>
#include <tupla.h>
#include <sdbproceso.h>
#include <sdbespacio.h>
#include <sdblinda.h>
#include <maestro.h>
#include <esclavo.h>

#define WSIZE 10

#define CREA_ENTERO(a) \
	a = (int *) malloc(sizeof(int))

#define BORRA_ENTERO(a) \
	free(a); a = NULL

#include <stdio.h>
struct registro{
	int numero;
	char palabra[10];
	double promedio;
};

int prueba( int argc, char *argv[] ) {

	estado *edo;

	sdblinda_iniciar(argc, argv);
	edo = sdbproceso_estado();

	if( SOYMAESTRO ( edo ) )
		coordinador();
	else if( SOYESCLAVO ( edo ) )
		esclavo();

	sdblinda_detener();
	printf("LA PRUEBA A TERMINADO\n");
	return 0;
}

void coordinador(){

	tupla t;
	int i = 0, j;
	TUPLA_NEW ( t, sizeof(i) );
	TUPLA_WRITE ( t, &i);

	for( j=0; j<10; j++){
		sdblinda_meter( "ida", t );
		printf( "Coordinador: Meti Entero i = %d\n", i );
		sdblinda_sacar( "regreso", t );
		TUPLA_READ ( &i, t );
		printf( "Coordinador: Recibi i modificado %d\n", i );
	}


}

void esclavo(){

	tupla t;
	int i, j;
	TUPLA_NEW( t, sizeof(i) );
	for(j = 0; j < 10; j++) {

		sdblinda_sacar( "ida", t );

		TUPLA_READ( &i, t );
		printf( "Esclavo: Recibi i = %d\n", i );
		i++;
		TUPLA_WRITE ( t, &i);

		sdblinda_meter( "regreso", t );
		printf( "Esclavo: Envie entero i = %d incrementado\n", i );
	}

}

int prueba_pthread( int argc, char *argv[] ) {
	return 0;
}
