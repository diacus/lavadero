/*
 * thash.c
 *
 *  Created on: 10/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thash.h>

/* unsigned int hash( char *key, unsigned int sz, unsigned int shift )
 *
 */

unsigned int hash( char *key, unsigned int sz, unsigned int shift ) {

	char xor = '\0', *s = key - 1;
	unsigned int bits, hash_val;
	double prod;

	bits = 1;
	while( *++s ) {
		ROTAR( *s, bits );
		bits++;
		xor ^= *s;
	}

	prod = (double) xor * GOLD;
	hash_val = (int) ((prod - floor(prod)) * shift);

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

/* unsigned int thash_insert( thash *t, void *value, char *key )
 *
 */

unsigned int thash_insert( thash *t, void *value, char *key ) {

	unsigned int index = hash( key, t->size, SHIFT );
	lista *elem = lista_new(value, key);
	lista_insert( *(t->table + index), elem );

	return index;
}

/* void *thash_remove( thash *t, char *key )
 *
 */

void *thash_remove( thash *t, char *key ) {

	unsigned int index = hash( key, t->size, SHIFT );
	lista *selected = *(t->table + index);

	res = lista_find( selected, key );
	if( res )
		selected = lista_remove( selected, key );

	return res;
}

/* void *thash_read( thash *t, char *key )
 *
 */

void *thash_read( thash *t, char *key ) {
	unsigned int index = hash( key, t->size, SHIFT );
	void *res = lista_find( *(t->table + index), key );
	return NULL;
}

/* int thash_flush( thash *t )
 *
 */

int thash_flush( thash *t ) {

	lista **ini, **fin;
	fin = t->table + t->size;
	for( ini = t->table; ini < fin; ini ++ ) {
		lista_delete(*ini);
		*ini = NULL;
	}

	return 0;

}

/* thash *thash_delete( thash *t )
 *
 */

thash *thash_delete( thash *t ) {

	thash_flush( t );
	free( t->table );
	free( t );

	return NULL;
}
