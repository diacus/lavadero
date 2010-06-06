/*
 * lista.c
 *
 *  Created on: 06/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lista.h>

/* lista *lista_new( void *inf, unsigned int sz, char *k )
 *
 * Constructor de un nodo de lista con que almacena un apuntador
 * info a una cadena de sz bytes etiquetados con la clave key.
 *
 * Devuelve un apuntador al nodo de lista creado.
 */

lista *lista_new( void *inf, char *k ) {
	lista *res = (lista *) malloc( sizeof(lista) );
	res->info = inf;
	res->key  = strdup(k);
	res->next = NULL;
	return res;
}

/* lista *lista_insert( lista *lst, lista *item )
 *
 * Inserta el nodo item en la lista lst, ordenandolo
 * por su clave
 */

lista *lista_insert( lista *lst, lista *item ) {
	lista *res = NULL;
	int dif;
	if ( lst ) {

		dif = strcmp ( lst->key, item->key );
		if( dif >= 0 ) {

			res = item;
			item->next = lst;

		} else if( dif < 0 ) {

			res = lst;
			lst->next = lista_insert( lst->next, item );

		}

	} else
		res = item;
	return res;
}

/* lista *lista_remove( lista *lst, char *k )
 *
 * Elimina el nodo con clave k de la lista lst.
 */

lista *lista_remove( lista *lst, char *k ) {

	lista *res = lst;

	if( lst ) {

		if ( !strcmp( k, lst->key ) ) { 			/* si las claves coinciden       */

			res = lst->next;						/* se elimina el nodo actual     */
			lst->next = NULL;
			lista_delete( lst );

		} else										/* En caso de que no coincidan   */
			          								/* el nodo a remover se busca en */
			lst->next = lista_remove(lst->next, k);	/* el resto de la lista          */

	} /*else {
		fprintf(
			stderr,
			"Error: no hay elementos etiquetados con la clave %s en la tabla.\n",
			k
		);
	}*/

	return res;

}

/* tupla lista_find( lista *lst, char *k )
 *
 * Devuelve la tupla almacenada en la lista
 * lst, con clave k.
 */

void *lista_find( lista *lst, char *k ) {

	void *res = NULL;

	if(lst)
		res = strcmp(k, lst->key) ? lista_find(lst->next, k) : lst->info;

	return res;
}

/* void *lista_delete( lista *lst )
 *
 */

void *lista_delete( lista *lst ) {
	void *res = NULL;
	if( lst && !lst->next ) {
		res = lst->info;
		lst->info = NULL;
		free( lst->key);
		free( lst );
	}
	return res;
}

/* lista *lista_finalize( lista *lst )
 *
 * Elimina la lista apuntada por lst.
 */

lista *lista_finalize( lista *lst ) {
	if(lst) {
		free(lst->key);
		free(lst->info);
		lista_delete(lst->next);
		free(lst);
	}
	return NULL;
}

