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

	if( edo->my_rank == 1 )
		coordinador();
	else if( edo->my_rank > 1 )
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
		sdblinda_meter( "saludo", t );
		printf( "Coordinador: Meti Entero i = %d\n", *(int *)(t+4) );
		sdblinda_sacar( "respuesta", t );
		TUPLA_READ ( &i, t );
		printf( "Coordinador: Recibi i modificado %d\n", *(int *)(t+4) );
	}


}

void esclavo(){

	tupla t;
	int i, j;
	TUPLA_NEW( t, sizeof(i) );
	for(j = 0; j < 10; j++) {
		sdblinda_sacar( "saludo", t );
		TUPLA_READ( &i, t );
		printf( "Esclavo: Recibi i = %d\n", *(int *)(t+4) );
		i++;
		TUPLA_WRITE ( t, &i);
		sdblinda_meter( "respuesta", t );
		printf( "Esclavo: Envie entero i = %d incrementado\n", *(int *)(t+4) );
	}

}
