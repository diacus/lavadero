/*
 * tupla.h
 *
 *  Created on: 05/05/2010
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
 * Declaración del tipo de dato abstracto tupla.
 */

#ifndef TUPLA_H_
#define TUPLA_H_

#include <stdlib.h>
#include <string.h>

/**
 * @typedef tupla Tipo de dato abstracto que se utiliza para guardar y comunicar
 * información entre los nodos que utilizan la memoria virtual distribuida.
 */

typedef char * tupla;

/** TUPLA_NEW(t, N)
 *
 * Macro para crear una tupla que almacene N bytes.
 *
 * Recibe
 *   t: Tiene que ser una variable de tipo tupla, es la tupla
 *      que se va a crear.
 *
 *   N: Tiene que ser una varable de tipo int, que indica el
 *      tamaño en bytes que podrá almacenar la tupla t.
 */

#define TUPLA_NEW(t, N) \
	t = (tupla) calloc( N + sizeof(int), sizeof(char) ); \
	*((int *) t) = N;
	/*memcpy(tupla, &N, sizeof(int))*/

/** TUPLA_READ(a,t)
 *
 * Macro utilizada para leer el contenido de la tupla t.
 *
 * Recibe:
 *   a: Debe ser un apuntador al espacio de memoria en el
 *      que se va a almacenar el contenido de la tupla t.
 *      el apuntador a, debe señalar a un espacio de memoria
 *      suficiente para escribir los datos almacenados en t.
 *
 *   t: Debe ser una variable de tipo tupla.
 */

#define TUPLA_READ(a,t) \
{\
	int size; \
	void *temp = t + sizeof(int); \
	size = *((int*) t); \
	memcpy(a, temp, size); \
}

/** TUPLA_WRITE(t,a)
 *
 * Macro utilizada para escribir en la tupla t, los datos
 * en el espacio de memoria apuntado por a.
 *
 * Recibe:
 *   t: Debe ser una variable de tipo tupla, del tamaño de
 *      los datos que se pretenden escribir en ella.
 *
 *   a: Apunta a los datos que se van a copiar a la tupla.
 */

#define TUPLA_WRITE(t,a) \
{\
	int size; \
	void *temp = t + sizeof(int); \
	memcpy( &size, t, sizeof(int) ); \
	memcpy(temp, a, size); \
}

#define TUPLA_INFO(t) t + sizeof ( int )
#define TUPLA_BYTES(t) *((int *) t)

/* TUPLA_SIZE(t)
 *
 * Macro utilizada para calcular el tamaño en bytes
 * ocupado por la tupla t.
 *
 * Requiere que el parámetro sea una variable de tipo
 * tupla.
 */

#define TUPLA_SIZE(t) *((int*) t) + sizeof(int)

/* TUPLA_DELETE(t)
 *
 * Macro utilizada para eliminar la tupla t.
 */

#define TUPLA_DELETE(t) { free(t); t = NULL; }


#endif /* TUPLA_H_ */
