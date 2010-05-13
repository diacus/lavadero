/*
 * tupla.c
 *
 *  Created on: 05/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <tupla.h>

/* tupla *tupla_new( unsigned int k, void *val )
 *
 */

tupla tupla_new( unsigned int N, ... ) {
	item elemento;
	tupla res = (tupla) calloc( N , sizeof(item) );
	int i, *c;
	va_list args;
	va_start(args, N);
	for (i=0; i< N; i++){
		c = (int*) malloc (sizeof(int));
		*c = va_arg(args, int);
		elemento = c;
		res[i] = elemento;
	}
	va_end(args);
	return res;
}

/* int tupla_print( tupla *t )
 *
 */

int tupla_print( tupla *t ) {
	//printf( "(%u,%X)\n", t->clave, (unsigned int) t->valor );
	return 0;
}

/* int tupla_delete( tupla *t )
 *
 */

int tupla_delete( tupla *t ) {
	free(t);
	return 0;
}
