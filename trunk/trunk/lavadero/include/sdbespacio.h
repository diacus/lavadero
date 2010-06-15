/*
 * sdbmaestro.h
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#ifndef SDBESPACIO_H_
#define SDBESPACIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <mpi.h>

#include <sdbproceso.h>
#include <pendiente.h>
#include <thash.h>
#include <tupla.h>


/* TABLESIZE : Número de claves en las tablas hash utilizadas */

#define TABLESIZE 1000

#define MULTITHREAD

#ifdef MULTITHREAD
#define NHILOS 2

typedef pthread_t       hilo;
typedef pthread_mutex_t candado;

typedef struct dt{
	char   *cliente;
	candado lock_tabla;
	candado lock_pendientes;
	candado lock_procesos;
} datos;

/* LIBERA_PROCESO(N, arg)
 *
 */

#define LIBERA_PROCESO(N, arg) \
	arg->cliente[N - MAESTRO - 1] = '\0'


/* datos *sdbespacio_getdatos()
 *
 * Obtiene un apuntador a los datos compartidos por los
 * hilos del espacio de tuplas.
 */

datos *sdbespacio_getdatos();

/* datos *sdbespacio_deletedatos( datos *d )
 *
 */

datos *sdbespacio_deletedatos( datos *d );

#endif

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

int sdbespacio_iniciar();

/* void *sdbespacio_atender( void *param )
 *
 */

void *sdbespacio_atender( void *param );

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

#endif /* SDBESPACIO_H_ */
