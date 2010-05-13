/*
 * pruebaG.c
 *
 *  Created on: 12/05/2010
 *      Author: ryuuba
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <tupla.h>

void prueba(){
	tupla ntupla;
	int i;
	printf("Esto es una prueba\n");
	ntupla = tupla_new(5, 'a', 2, 3, 55, 120);
	printf("direccion de tupla nueva = %d\n",ntupla);
	for(i=0;i<5;i++)
		printf("ntupla[%d] = %d\n",i,*(int *)(ntupla[i]));
}
