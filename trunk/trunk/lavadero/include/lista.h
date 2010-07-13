/*
 * lista.h
 *
 *  Created on: 10/05/2010
 *      Author: diacus
 */

/**
 * @file
 * @author Giovanni Medrano <ryubba@gmail.com>
 * @author Diego Guzmán <dr.guzsant@gmail.com>
 *
 * @version 1.0
 *
 * @section Descripción
 *
 * Declaración del tipo de dato abstracto lista.
 */

#ifndef LISTA_H_
#define LISTA_H_

#include <tupla.h>

/** @typedef Tipo lista:
 *
 * las variables de tipo lista son nodos de lista ligada
 * que contienen:
 *   + void       *info 
 *   + char       *key 
 *   + struct lst *next 
 */

typedef struct lst {
	void *info;
	char *key;
	struct lst *next;
} lista;

/* lista *lista_new( void *inf, char *k )
 *
 * Constructor de un nodo de lista con que almacena un apuntador
 * info a una cadena de sz bytes etiquetados con la clave key.
 *
 * Devuelve un apuntador al nodo de lista creado.
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

/* tupla *lista_find( lista *lst, char *k )
 *
 * Devuelve la tupla almacenada en la lista
 * lst, con clave k.
 */

void *lista_find( lista *lst, char *k );

/* lista *lista_delete( lista *lst )
 *
 */

void *lista_delete( lista *lst );

/* lista *lista_finalize( lista *lst )
 *
 * Elimina la lista lst.
 */

lista *lista_finalize( lista *lst );

#endif /* LISTA_H_ */
