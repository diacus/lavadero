/*
 * tupla.c
 *
 *  Created on: 05/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <stdlib.h>
#include <tupla.h>

/* tupla *tupla_new( unsigned int k, void *val )
 *
 */

tupla *tupla_new( unsigned int k, void *val ) {
	tupla *res = (tupla *) malloc( sizeof(tupla) );
	res->clave = k;
	res->valor = val;
	return res;
}

/* int tupla_print( tupla *t )
 *
 */

int tupla_print( tupla *t ) {
	printf( "(%u,%X)\n", t->clave, t->valor );
	return 0;
}

/* int tupla_delete( tupla *t )
 *
 */

int tupla_delete( tupla *t ) {
	free(t);
	return 0;
}
