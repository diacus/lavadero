/*
 * thash.h
 *
 *  Created on: 10/05/2010
 *      Author: diacus
 */

#ifndef THASH_H_
#define THASH_H_

#include <lista.h>

#define GOLD 1.6180339887498949
#define SHIFT 10e7

#define ROTAR( c, n ) \
	c = (c >> (n%8)) ^ ((c % (1 << (n%8))) << (8 - (n%8)))

/* Type thash
 *
 */

typedef struct th {
	unsigned int size;
	lista **table;
} thash;

/* unsigned int hash( char *key, unsigned int sz, unsigned int shift )
 *
 */

unsigned int hash( char *key, unsigned int sz, unsigned int shift );

/* thash *thash_new( unsigned int sz )
 *
 */

thash *thash_new( unsigned int sz );

/* unsigned int thash_insert( thash *t, void *value, char *key )
 *
 */

unsigned int thash_insert( thash *t, void *value, char *key );

/* void *thash_remove( thash *t, char *key )
 *
 */

void *thash_remove( thash *t, char *key );

/* void *thash_read( thash *t, char *key )
 *
 */

void *thash_read( thash *t, char *key );

/* int thash_flush( thash *t )
 *
 */

int thash_flush( thash *t );

/* thash *thash_delete( thash *t )
 *
 */

thash *thash_delete( thash *t );

#endif /* THASH_H_ */
