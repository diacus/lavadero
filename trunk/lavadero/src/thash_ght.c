/*
 * thash.c
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
 * Implementación de funciones para utilizar una tabla hash como
 * espacio de tuplas, o lista de pendientes.
 */

#include <thash.h>

#ifndef HECHIZA
#include <string.h>
#include <lista.h>

/**
 * Función construcora, crea una nueva tabla hash con sz entradas.
 *
 * @param sz el número de entradas que aceptará la tabla hash.
 * @return Devuelve un apuntador a la tabla hash recién creada.
 */

thash *thash_new( unsigned int sz ) { return ght_create(sz); }

/**
 *
 * Función para insrtar un elemento en la tabla hash.
 *
 * @param *t Apuntador a la tabla hash que recibe el objeto nuevo.
 * @param *value Apuntador al objeto que se va a insertar.
 * @param *key Clave con la que se va a insertar el elemento nuevo.
 *
 * @return Devuelve un entero que indica si la operación fué exitosa.
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

/**
 *
 * Retira el dato etiquetado con la clave key de la tabla apuntada por t.
 *
 * @param *t Un apuntador a la tabla hash de la que se va a eliminar el elemento.
 * @param *key clave del elemento que se desea eliminar.
 *
 * @return Devuelve un apuntador al dato retirado de la tabla, y escribe el tamaño
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

/**
 *
 * Función para leer un elemento de la tabla hash.
 *
 * @param *t Un apuntador a la tabla hash de la que se va a consultar el elemento.
 * @param *key clave del elemento que se desea consultar.
 *
 * @return Devuelve un apuntador al elemento encontrado.
 *
 */

void *thash_read( thash *t, char *key ) {
	return ght_get( t, strlen(key), key );
}

/**
 *
 * Elimina todos los elementos de la tabla.
 *
 * @param *t Un apuntador a la tabla hash de la que se van a eliminar los elementos.
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

/**
 *
 * Función destructora de la tabla hash
 *
 * @param *t Un apuntador a la tabla hash de la que se va a eliminar.
 * @return Esta función devuelve un apuntador nulo en caso de éxito.
 */

thash *thash_finalize( thash *t ) {
	ght_finalize(t);
	return NULL;
}

#endif
