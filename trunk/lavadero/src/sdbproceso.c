/*
 * sdbproceso.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sdbproceso.h>

#include <tupla.h>


/* estado *sdbproceso_estado()
 *
 * Función para crear las variables de estado del proceso
 * y obtener un apuntador al registro donde se alojan.
 *
 * Devuelve un apuntador a una variable de tipo estado
 */

estado *sdbproceso_estado() {
	static int creado = 0;
	static estado *est = NULL;

	if( ! creado ) {
		est = (estado *) malloc( sizeof(estado) );
		creado++;
	}

	return est;
}

/* char *sdbproceso_pack( char *key, tupla *data )
 *
 * Función para empaquetar la tupla data y su clave key, en una sola
 * porción de memoria, para ser enviados a la memoria compartida.
 *
 * +-------+-----------------------------------------+
 * | clave |                  tupla                  |
 * +-------+-----------------------------------------+
 *
 * |<--longitud de la clave + n bytes de la tupla -->|
 *
 * La función devuelve un apuntador al espacio de memoria que
 * almacena el "paquete".
 *
 */

char *sdbproceso_pack( char *key, tupla data ) {

	int sz = TUPLA_SIZE(data);
	unsigned int shift = strlen(key) + 1;						/*tamaño (shift) en bytes de la clave*/
	unsigned int pack_size = sz + shift;						/*tamaño del paquete a enviar*/
	char *package = (char *) calloc( pack_size, sizeof(char) );	/*Reservación de memoria para el paquete*/


	memcpy( package, key, shift );										/* Copiando la clave de la tupla */

	/* Copiando la tupla al paquete */
	memcpy( package + shift, data, sz );

	return package;
}

/* int sdbproceso_unpack( char *msg, unsigned int sz, char **key, void **data)
 *
 * Función para descomponer el mensaje apuntado por msg de tamaño sz.
 *
 * Devuelve en el apuntador data los datos recuperados, la cadena
 * apuntada por key con la clave de la tupla y el tamaño en bytes de la tupla
 */

int sdbproceso_unpack( char *msg, unsigned int sz, char **key, tupla *data) {

	unsigned int shift = strlen(msg) + 1;
	*key = (char *) calloc( shift, sizeof(char) );

	strcpy( *key, msg );
	TUPLA_NEW(*data, sz - shift - sizeof(int) );
	TUPLA_WRITE( *data, msg + shift );

	return TUPLA_BYTES(*data);

}