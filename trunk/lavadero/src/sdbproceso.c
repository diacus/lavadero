/*
 * sdbproceso.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <stdlib.h>
#include <string.h>
#include <sdbproceso.h>

/* estado *sdbproceso_estado()
 *
 * Función para crear las variables de estado del proceso
 * y obtener un apuntador al registro donde se alojan.
 *
 * Devuelve un apuntador a una variable de tipo estado
 */

estado *sdbproceso_estado() {
	static int creado = 0;
	static estado *est;

	if( ! creado ) {
		est = (estado *) malloc( sizeof(estado) );
		creado++;
	}

	return est;
}

/* char *sdbproceso_pack( unsigned int *nbytes, void *data, unsigned int *sz, char *key )
 *
 * Función para empaquetar los *sz bytes apuntados por data y su
 * clave key, en una sola porción de memoria, para ser enviados
 * a la memoria compartida.
 *
 * La función devuelve un apuntador al espacio de memoria que
 * almacena el "paquete" y escribe en el entero apuntado por
 * nbytes el tamaño de este.
 */

char *sdbproceso_pack( unsigned int *nbytes, void *data, unsigned int *sz, char *key ) {

	unsigned int shift = strlen(key) + 1;
	unsigned int pack_size = *sz + shift + sizeof( unsigned int );
	char *package = (char *) calloc( pack_size, sizeof(char) );

	strcpy( package, key ); /* Falta completar la implementación */
}

/* void *sdbproceso_unpack( unsigned int *nbytes, char **key, char *msg )
 *
 * Función para descomponer el mensaje apuntado por msg.
 *
 * Devuelve un apuntador a los datos recuperados, escribe en el entero
 * apuntado por nbytes el tamaño en bytes de dichos datos y en la cadena
 * apuntada por key la clave con que se etiqueta.
 */

void *sdbproceso_unpack( unsigned int *nbytes, char* key, char *msg );
