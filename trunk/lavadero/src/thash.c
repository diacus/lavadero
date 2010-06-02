/*
 * thash.c
 *
 *  Created on: 10/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <thash.h>

#ifdef HECHIZA

/* void rotabit( char *c, unsigned int shift )
 *
 */

void rotabit( char *c, unsigned int shift ) {
	unsigned int n = shift % 8;
	char head, tail;

	head = *c >> n;
	tail = (*c % (1 << n)) << (8 - n);
	*c = head ^ tail;
}

/* unsigned int hash( char *key, unsigned int sz, unsigned int shift )
 *
 * Calcula el índice correspondiente a la clave key, dentro de una tabla hash que tiene
 * sz posibles particiones.
 *
 */

unsigned int hash( char *key, unsigned int sz, unsigned int shift ) {

	char xor = '\0', *cad, *s;
	unsigned int hash_val, bits = 0;
	double prod;

	cad = s = strdup(key);
	while( *s ) {
		rotabit( s, ++bits );
		xor ^= *s++;
	}

	prod = (double) xor * GOLD;
	hash_val = (int) ((prod - floor(prod)) * shift);
	free(cad);
	return hash_val % sz;

}

/* thash *thash_new( unsigned int sz )
 *
 */

thash *thash_new( unsigned int sz ) {
	thash *res = (thash *) malloc( sizeof(thash) );
	res->table = (lista **) calloc( sz, sizeof(lista *) );
	res->size = sz;
	return res;
}

/* unsigned int thash_insert( thash *t, void *value, unsigned int sz, char *key )
 *
 */

unsigned int thash_insert( thash *t, void *value, char *key ) {

	unsigned int index = hash( key, t->size, SHIFT );
	lista **selected, *elem;
	elem = lista_new(value, key);
	selected = t->table + index;
	*selected = lista_insert( *selected, elem );

	return index;
}

/* void *thash_remove( thash *t, char *key )
 *
 * Retira el dato etiquetado con la clave key de la tabla apuntada por t.
 *
 * Devuelve un apuntador al dato retirado de la tabla, y escribe el tamaño
 * del dato en el entenro apuntado por sz.
 */

void *thash_remove( thash *t, char *key ) {

	unsigned int index = hash( key, t->size, SHIFT );
	lista *selected = *(t->table + index);
	void *res = lista_find( selected, key );

	printf("thash_remove: elemento hasheado - %s, %d\n", key, index );
	if( res ) {
		selected = lista_remove( selected, key );
	} else
		printf( "thash_remove: El elemento con clave %s no fue encontrado\n", key );

	return res;
}

/* void *thash_read( thash *t, unsigned int *sz, char *key )
 *
 */

void *thash_read( thash *t, char *key ) {
	unsigned int index = hash( key, t->size, SHIFT );
	void *res = lista_find( *(t->table + index), key );
	return res;
}

/* int thash_flush( thash *t )
 *
 */

int thash_flush( thash *t ) {

	lista **ini, **fin;
	fin = t->table + t->size;
	for( ini = t->table; ini < fin; ini ++ ) {
		if( *ini ) {
			lista_finalize(*ini);
			*ini = NULL;
		}
	}

	return 0;

}

/* thash *thash_finalize( thash *t )
 *
 */

thash *thash_finalize( thash *t ) {

	thash_flush( t );
	free( t->table );
	free( t );

	return NULL;
}

#endif
