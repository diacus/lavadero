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

/* #define ROTAR( c, n )
 *
 * Esta macro gira los bits de c en dirección a los bits menos significativos
 * n lugares.
 *
 */

#define ROTAR( c, n ) \
	c = (c >> (n%8)) ^ ((c % (1 << (n%8)) << (8 - (n%8))))

/* Type thash
 *
 * Tipo de Dato Abstracto que representa una tabla hash centralizada
 *
 */

typedef struct th {
	unsigned int size;
	lista **table;
} thash;

/* void rotabit( char *c, unsigned int shift )
 *
 */

void rotabit( char *c, unsigned int shift );

/* unsigned int hash( char *key, unsigned int sz, unsigned int shift )
 *
 * Calcula el índice correspondiente a la clave key, dentro de una tabla hash que tiene
 * sz posibles particiones.
 *
 * Devuelve el índice donde debe guardarse el dato.
 *
 */

unsigned int hash( char *key, unsigned int sz, unsigned int shift );

/* thash *thash_new( unsigned int sz )
 *
 * Función constructora de una tabla hash, de "tamaño" sz-
 *
 * Devuelve un apuntador a la tabla hash recién creada.
 */

thash *thash_new( unsigned int sz );

/* unsigned int thash_insert( thash *t, void *value, char *key )
 *
 * Almacena el valor apuntado por value, etiquetado con la clave key
 * y de tamaño sz, dentro de la tabla hash apuntada por t.
 */

unsigned int thash_insert( thash *t, void *value, unsigned int sz, char *key );

/* void *thash_remove( thash *t, char *key )
 *
 * Retira el dato etiquetado con la clave key de la tabla apuntada por t.
 *
 * Devuelve un apuntador al dato retirado de la tabla
 */

void *thash_remove( thash *t, unsigned int *sz, char *key );

/* void *thash_read( thash *t, unsigned int *sz, char *key )
 *
 * Busca en la tabla apuntada por t, el dato etiquetado con la
 * clave key.
 *
 * La función devuelve un apuntador al objeto encontrado, y escribe
 * en el entero apuntado por sz, el tamaño de este.
 */

void *thash_read( thash *t, unsigned int *sz, char *key );

/* int thash_flush( thash *t )
 *
 * Elimina todas las entradas alamacenadas en la tabla
 * apuntada por t.
 */

int thash_flush( thash *t );

/* thash *thash_delete( thash *t )
 *
 */

thash *thash_delete( thash *t );

#endif /* THASH_H_ */
