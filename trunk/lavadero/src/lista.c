/**
 * @file
 * @author Giovanni Medrano <ryubba@gmail.com>
 * @author Diego Guzmán <dr.guzsant@gmail.com>
 *
 * @version 1.0
 *
 * @section Descripción
 *
 * Implementación del tipo de dato abstracto lista,
 * el cual es empleado para perimitir duplicidad de clabes en
 * el espacio de tuplas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lista.h>

/** lista *lista_new( void *inf, unsigned int sz, char *k )
 *
 * Constructor de un nodo de lista con que almacena un apuntador
 * inf a una cadena de sz bytes etiquetados con la clave key.
 *
 * @param *inf un apuntador a la información del nuevo nodo.
 * @param sz tamaño del dato apuntado por inf.
 * @param *k cadena de caracteres que representa la clave del dato apuntado por inf.
 * @return Devuelve un apuntador al nodo de lista creado.
 */

lista *lista_new( void *inf, char *k ) {
	lista *res = (lista *) malloc( sizeof(lista) );
	res->info = inf;
	res->key  = strdup(k);
	res->next = NULL;
	return res;
}

/** lista *lista_insert( lista *lst, lista *item )
 *
 * Inserta el nodo item en la lista lst, ordenandolo
 * por su clave.
 *
 * @param *lst apuntador a la lista en la que se quiere insertar un elemento.
 * @param *item apuntador al elemento de la lista que se quiere insertar en lst.
 *
 * @return Devuelve un apuntador a la lista resultante.
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

/** lista *lista_remove( lista *lst, char *k )
 *
 * Elimina el nodo con clave k de la lista lst.
 *
 * @param *lst apuntador a la lista de la que se quiere remover un elemento.
 * @param *k clave del elemento que se quiere remover de la lista.
 *
 * @return Devuelve un apuntador a la lista resultante.
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

/** tupla lista_find( lista *lst, char *k )
 *
 * Devuelve la tupla almacenada en la lista
 * lst, con clave k.
 *
 * @param *lst Apuntador a la lista en la que se buscará el nodo.
 * @param k clave del nodo que se buscará en la lista
 *
 * @return devuelve la tupla correspondiente a la clave dada
 */

void *lista_find( lista *lst, char *k ) {

	void *res = NULL;

	if(lst)
		res = strcmp(k, lst->key) ? lista_find(lst->next, k) : lst->info;

	return res;
}

/* void *lista_delete( lista *lst )
 *
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

/** lista *lista_finalize( lista *lst )
 *
 * Elimina la lista apuntada por lst.
 *
 * @param *lst Es un apuntador a la lista que se va a eliminar.
 * @return Devuelve un apuntador a nulo.
 */

lista *lista_finalize( lista *lst ) {
	if(lst) {
		free(lst->key);
		free(lst->info);
		lista_finalize(lst->next);
		free(lst);
	}
	return NULL;
}

