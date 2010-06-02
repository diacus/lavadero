/*
 * thash.c
 *
 *  Created on: 10/05/2010
 *      Author: diacus
 */

#include <thash.h>

#ifndef HECHIZA
#include <string.h>
#include <lista.h>

/* thash *thash_new( unsigned int sz )
 *
 */

thash *thash_new( unsigned int sz ) { return ght_create(sz); }

/* unsigned int thash_insert( thash *t, void *value, unsigned int sz, char *key )
 *
 */

unsigned int thash_insert( thash *t, void *value, char *key ) {

	int len = strlen(key);
	lista *lst, *item;
	item = lista_new( value, key );
	lst = ght_remove( t, len, key );
	lst = lista_insert( lst, item );
	return ght_insert( t, lst, len, key );

}

/* void *thash_remove( thash *t, char *key )
 *
 * Retira el dato etiquetado con la clave key de la tabla apuntada por t.
 *
 * Devuelve un apuntador al dato retirado de la tabla, y escribe el tamaño
 * del dato en el entenro apuntado por sz.
 */

void *thash_remove( thash *t, char *key ) {

	int len = strlen(key);
	void *res = NULL;
	lista *lst;
	lst = ght_remove( t, len, key );
	res = lista_find( lst, key );
	lst = lista_remove( lst, key );
	ght_insert( t, lst, len, key );

	return res;

}

/* void *thash_read( thash *t, unsigned int *sz, char *key )
 *
 */

void *thash_read( thash *t, char *key ) {
	return ght_get( t, strlen(key), key );
}

/* int thash_flush( thash *t )
 *
 */

int thash_flush( thash *t ) {

	ght_iterator_t iterador;
	lista *i, *tmp;
	void *k;

	for( i = (char *) ght_first(t, &iterador, k ); i ; i = (char *) ght_next(t, &iterador, k ) )
		tmp = lista_finalize(i);

	return 0;

}

/* thash *thash_finalize( thash *t )
 *
 */

thash *thash_finalize( thash *t ) {
	ght_finalize(t);
	return NULL;
}

#endif
