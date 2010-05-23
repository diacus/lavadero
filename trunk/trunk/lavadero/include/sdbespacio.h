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

/* TABLESIZE : Númrto de claves en las tablas hash utilizadas */

#define TABLESIZE 1000

/* Tipo: operacion
 *
 * Es una de las dos operaciones que pueden provocar el bloqueo de una
 * tarea.
 *
 *   Valores
 *     - LEER     : Cuando la tarea solicita una tupla en modo lectura.
 *     - Eliminar : Cuando la tarea solicita una tupla en modo escritura.
 */

typedef enum oper { LEER = 200, ELIMINAR = 201 } operacion;

/* Registro: pendiente
 *
 * Estructura para almacenar las solicigudes pendientes.
 *
 *   Campos
 *     - key     : La clave de la tupla pendiente
 *     - cliente : El identificador del cliente que solicita la tupla
 *     - op      : La operación que el cliente quiere ejecutar sobre la tupla.
 */

typedef struct pnd {
	char *key;
	unsigned int cliente;
	operacion op;
} pendiente;

/* pendiente *sdbespacio_newpendiente()
 *
 * Función para crear un nuevo registro de solicitudes
 * pendientes.
 *
 * Devuelve un apuntador al registro recién creado.
 */

pendiente *sdbespacio_newpendiente();

/* int sdbespacio_deletependiente( pendiente *p )
 *
 * Función para liberar el espacio de memoria donde se almacena
 * una solicitud pendiente.
 *
 * Devuelve un entero igual a cero en caso de éxito, y un entero
 * distinto de cero en caso de error.
 */

int sdbespacio_deletependiente( pendiente *p );

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

unsigned int sdbespacio_atiendeGrab( char *key, unsigned int src );

#endif /* SDBMAESTRO_H_ */
