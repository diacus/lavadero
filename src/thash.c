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

/* unsigned int hash( char *key )
 *
 */

unsigned int hash( char *key, unsigned int sz ) {
	char xor = '\0', *s = key - 1;
	unsigned int hash_val;
	double prod;

	while( *++s )
		xor ^= *s;

	prod = (double) xor * GOLD;
	hash_val = (int) ((prod - floor(prod)) * 10.0e4);

	return hash_val % sz;

}

/* thash *thash_new( unsigned int sz )
 *
 */

thash *thash_new( unsigned int sz ) {
	return NULL;
}

/* unsigned int thash_insert( thash *t, void *value, char *key )
 *
 */

unsigned int thash_insert( thash *t, void *value, char *key ) {
	return 0;
}

/* void *thash_remove( thash *t, char *key )
 *
 */

void *thash_remove( thash *t, char *key ) {
	return NULL;
}

/* void *thash_read( thash *t, char *key )
 *
 */

void *thash_read( thash *t, char *key ) {
	return NULL;
}

/* int thash_flush( thash *t )
 *
 */

int thash_flush( thash *t ) {
	return 0;
}

/* thash *thash_delete( thash *t )
 *
 */

thash *thash_delete( thash *t ) {
	return NULL;
}

