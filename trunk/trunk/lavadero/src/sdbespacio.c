/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <sdbespacio.h>

#define TABLESIZE 1000

/* thash *sdbmaestro_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbmaestro_gethash() {
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

/* int sdbmaestro_start()
 *
 * Función para inicializar el especio de tuplas.
 */

int sdbmaestro_start() {

	thash *tabla = sdbmaestro_gethash();
	estado *edo = sdbproceso_estado();
	char *message;

	while( edo->tag != FIN ) {

	}

	return 0;
}
