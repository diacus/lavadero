/*
 * sdbmaestro.h
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#ifndef SDBMAESTRO_H_
#define SDBMAESTRO_H_

#include <sdbmaestro.h>
#include <sdbproceso.h>
#include <thash.h>

/* thash *sdbmaestro_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbmaestro_gethash();

/* sdbmaestro_start()
 *
 * Función para inicializar el proceso maestro.
 */

int sdbmaestro_start();

#endif /* SDBMAESTRO_H_ */
