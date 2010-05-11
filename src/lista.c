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

/* lista *lista_new( void *inf, char *key )
 *
 * Constructor de un nodo de lista con información info
 * y clave key.
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
		if( dif > 0 ) {

			res = item;
			item->next = lst;

		} else if( dif < 0 ) {

			res = lst;
			lst->next = lista_insert( lst->next, item );

		} else {

			fprintf(
				stderr,
				"Error: La clave %s ya esta en uso, por favor elige otra\n",
				item->key
			);
			res = lst;

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

	lista *res;

	if( lst ) {

		if ( !strcmp( k, lst->key ) ) { 		/* si las claves coinciden */

			res = lst->next;					/* se elimina el nodo actual */
			lst->next = NULL;
			lista_delete( lst );

		} else {								/* En caso de que no coincidan */
			res = lst;							/* el nodo a remover se busca en */
			lst->next = lista_remove(lst, k);	/* el resto de la lista */
		}
	} else {
		res = NULL;
		fprintf(
			stderr,
			"Error: no hay ningun elemento con la clave %s en la tabla\n",
			k
		);
	}

	return res;

}

/* void *lista_find( lista *lst, char *k )
 *
 * Devuelve el apuntador al dato almacenado en la lista
 * lst, con clave k.
 */

void *lista_find( lista *lst, char *k ) {

	void *res;

	if(lst)
		res = strcmp(k, lst->key) ? lista_find(lst->next, k) : lst->info;
	else
		res = NULL;

	return res;
}

/* lista *lista_delete( lista *lst )
 *
 * Elimina la lista lst.
 */

lista *lista_delete( lista *lst ) {
	if(lst) {
		free(lst->info);
		free(lst->key);
		lista_delete(lst->next);
		free(lst);
	}
	return NULL;
}

