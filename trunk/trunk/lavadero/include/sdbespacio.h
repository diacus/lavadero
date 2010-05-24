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
#include <mpi.h>

/* TABLESIZE : Númrto de claves en las tablas hash utilizadas */

#define TABLESIZE 1000

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
	int op;
} pendiente;


/* NEWPENDIENTE(x)
 *
 * Macro para crear un nuevo registro de solicitudes
 * pendientes.
 *
 * Requiere que el parámetro sea un apuntador a pendiente.
 */

#define NEWPENDIENTE(x) x = (pendiente *) malloc(sizeof(pendiente))

/* DELETEPENDIENTE(x)
 *
 * Macro para liberar el espacio de memoria ocupado
 * por un pendiente.
 *
 * Requiere que el parámetro sea un apuntador a pendiente.
 */

#define DELETEPENDIENTE(x) free(x)

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

/* unsigned int sdbespacio_atiendeStore( char * message, int sz )
 *
 */

unsigned int sdbespacio_atiendeStore( char * message, int sz );

/* int sdbespacio_atiendeGrab( char *key, unsigned int src )
 *
 * Rutina para atender la petición Grab de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeGrab( char *key, unsigned int src );

/* int sdbespacio_atiendeRead( char *key, unsigned int src )
 *
 * Rutina para atender la petición Read de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeRead( char *key, unsigned int src );

/* int sdbespacio_atiendeDrop( char *key )
 *
 * Rutina para atender la petición Drop.
 */

int sdbespacio_atiendeDrop( char *key );

#endif /* SDBMAESTRO_H_ */
