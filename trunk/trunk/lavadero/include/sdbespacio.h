/*
 * sdbmaestro.h
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#ifndef SDBMAESTRO_H_
#define SDBMAESTRO_H_

#include <sdbespacio.h>
#include <sdbproceso.h>
#include <thash.h>

/* thash *sdbespacio_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbespacio_gethash();

/* thash *sdbespacio_getpendientes()
 *
 * Funcipon para obtener una referencia al espacio en el que
 * se van a almacenar las peticiones pendientes.
 */

thash *sdbespacio_getpendientes();

/* sdbespacio_start()
 *
 * Función para inicializar el proceso maestro.
 */

int sdbespacio_start();

/* int sdbespacio_atiendeGrab( char *key, unsigned int src )
 *
 * Rutina para atender la petición Grab de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeGrab( char *key, unsigned int src );

#endif /* SDBMAESTRO_H_ */
