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
#include <tupla.h>
#include <ght_hash_table.h>
#include <mpi.h>

typedef ght_hash_table_t thash;

/* TABLESIZE : Número de claves en las tablas hash utilizadas */

#define TABLESIZE 1000

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

/* void sdbespacio_iniciar()
 *
 * Función para inicializar el proceso maestro.
 */

void sdbespacio_iniciar();

/* unsigned int sdbespacio_atiendeMeter( char * message, int sz, thash *tabla )
 *
 */

unsigned int sdbespacio_atiendeMeter( char * message, int sz, thash *tabla );

/* int sdbespacio_atiendeSacar( char *key, unsigned int src, thash *tabla )
 *
 * Rutina para atender la petición Sacar de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeSacar( char *key, unsigned int src, thash *tabla );

/* int sdbespacio_atiendeLeer( char *key, unsigned int src, thash *tabla )
 *
 * Rutina para atender la petición Leer de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeLeer( char *key, unsigned int src, thash *tabla );

/* int sdbespacio_atiendeSuprimir( char *key, thash *tabla )
 *
 * Rutina para atender la petición Suprimir.
 */

int sdbespacio_atiendeSuprimir( char *key, thash *tabla );

#endif /* SDBMAESTRO_H_ */
