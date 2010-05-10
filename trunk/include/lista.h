/*
 * lista.h
 *
 *  Created on: 10/05/2010
 *      Author: diacus
 */

#ifndef LISTA_H_
#define LISTA_H_

typedef struct lst {
	void *info;
	char *key;
	struct lst *next;
} lista;

/* lista *lista_new( void *inf, char *k )
 *
 * Constructor de un nodo de lista con información info
 * y clave key.
 */

lista *lista_new( void *inf, char *k );

/* lista *lista_insert( lista *lst, lista *item )
 *
 * Inserta el nodo item en la lista lst, ordenandolo
 * por su clave
 */

lista *lista_insert( lista *lst, lista *item );

/* lista *lista_remove( lista *lst, char *k )
 *
 * Elimina el nodo con clave key de la lista lst.
 */

lista *lista_remove( lista *lst, char *k );

/* void *lista_find( lista *lst, char *k )
 *
 * Devuelve el apuntador al dato almacenado en la lista
 * lst, con clave k.
 */

void *lista_find( lista *lst, char *k );

/* lista *lista_delete( lista *lst )
 *
 * Elimina la lista lst.
 */

lista *lista_delete( lista *lst );

#endif /* LISTA_H_ */
