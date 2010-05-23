/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <sdbespacio.h>

#define TABLESIZE 1000

/* thash *sdbespacio_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbespacio_gethash() {
	static int creadaHash = 0;
	static thash *tabla = NULL;

	if( ! creadaHash ) {
		creadaHash ++;
		/* Esta parte puede ser parametrizada con */
		/* un archivo de configuración            */
		tabla = thash_new(TABLESIZE);
	}

	return tabla;
}

/* int sdbespacio_start()
 *
 * Función para inicializar el especio de tuplas.
 */

int sdbespacio_start() {

	/* thash *tabla = sdbespacio_gethash();*/
	estado *edo = sdbproceso_estado();
	/* char *message; */

	while( edo->tag != FIN ) {

	}

	return 0;
}


/* int sdbespacio_atiendeGrab( char *key, unsigned int src )
 *
 * Rutina para atender la petición Grab de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeGrab( char *key, unsigned int src ) {
	return 0;
}
