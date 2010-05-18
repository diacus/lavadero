/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <sdbmaestro.h>

/* thash *sdbmaestro_gethash()
 *
 */

thash *sdbmaestro_gethash() {
	static int creada = 0;
	static thash *tabla = NULL;

	if( ! creada ) {
		creada ++;
		/* Esta parte puede ser parametrizada con */
		/* un archivo de configuración            */
		tabla = thash_new(1000);
	}

	return tabla;
}

/* int sdbmaestro_start()
 *
 */

int sdbmaestro_start() {
	thash *tabla = sdbmaestro_gethash();
	estado *edo = sdbproceso_estado();

	return 0;
}
