/*
 * sdbproceso.h
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#ifndef SDBPROCESO_H_
#define SDBPROCESO_H_

#include <mpi.h>
#include <string.h>
#include <tupla.h>

#define TIEMPO1	   10000 /** tiempo en decimas de segundo */
#define TIEMPO2	   100000 /** tiempo en decimas de segundo */
#define MENSAJES   333 /** tiempo en decimas de segundo */
#define LINDA0     0 /** Identificador del proceso que administra el espacio de tuplas primario.     */
#define LINDA1     1 /** Identificador del proceso que administra el espacio de tuplas secundario.     */
#define MAESTRO    2 /** Identificador del proceso que administra la aplicación             */
#define NSITES     2/** Identificador del proceso que administra la aplicación             */
#define STORE    100 /** Etiqueta para un mensaje que envía una tupla para que se almacene. */
#define GRAB     101 /** Etiqueta para un mensaje de solicitud de tupla.                    */
#define READ     102 /** Etiqueta para un mensaje que busca eliminar una tupla del espacio. */
#define DROP   	 103 /** Etiqueta para un mensaje que busca eliminar una tupla del espacio. */
#define SIZE     104 /** Etiqueta para un mensaje que transmite el tamaño de un dato.       */
#define DATA	 105 /** Etiqueta para un mensaje que transmite una tupla.                  */
#define BEGIN    106 /** Etiqueta inicial.                                                  */
#define END      107 /** Etiqueta final.                                                    */
#define ACK      108 /** Etiqueta acuse de recibo                                           */
#define UNATTENDED 109 /** Etiqueta para atender pendiente								   */
#define SAVE 110 /** Etiqueta para atender pendiente								   */

/** SOYESCLAVO(e) e->my_rank
 *
 * Predicado que es verdadero si el proceso es quien
 * realiza el trabajo.
 */

#define SOYESCLAVO(e) e->my_rank > NSITES


/** SOYESPACIO(e) e->my_rank
 *
 * Predicado que es verdadero si el proceso es quien
 * administra el espacio de tuplas.
 */

#define SOYESPACIO(e) e->my_rank < NSITES

/** SOYMAESTRO(e) e->my_rank
 *
 * Predicado que es verdadero si el proceso es quien
 * administra la aplicación que es soportada por el
 * middleware.
 */

#define SOYMAESTRO(e) e->my_rank == NSITES

/** SOYPRIMARIO(e) e->my_rank
 *
 * Predicado que es verdadero si el proceso es quien
 * administra el espacio de tuplas primario
 */

#define SOYPRIMARIO(e) e->my_rank == LINDA0

/** SOYSECUNDARIO(e) e->my_rank
 *
 * Predicado que es verdadero si el proceso es quien
 * administra el espacio de tuplas secundario
 */

#define SOYSECUNDARIO(e) e->my_rank == LINDA1

/** DELETE_MESSAGE(s)
 *
 * Libera la memoria apuntada por s memoria de forma
 * segura.
 */

#define DELETE_MESSAGE(s) {free(s); s = NULL;}

/** Registro: estado
 *
 * Estructura para almacenar las variables que identifican
 * a cada proceso dentro de MPI.
 */

typedef struct edo {
	int			my_rank;	/* Identificador de proceso                */
	int			num_procs;	/* Número de procesos activos              */
	int			tag;    	/* Etiqueta para el mensaje                */
	char		*message;   /* Apuntador al mensaje a enviar o recibir */
	MPI_Status	status ;	/* Estado de la comunicación               */
	MPI_Request request;	/*  */
} estado;

/** estado *sdbproceso_estado()
 *
 * Función para crear las variables de estado del proceso
 * y obtener un apuntador al registro donde se alojan.
 *
 * Devuelve un apuntador a una variable de tipo estado
 */

estado *sdbproceso_estado();

/** char *sdbproceso_pack( char *key, tupla *data )
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

char *sdbproceso_pack( char *key, tupla data );

/** int sdbproceso_unpack( char *msg, unsigned int sz, char **key, tupla *data)
 *
 * Función para descomponer el mensaje apuntado por msg de tamaño sz.
 *
 * Devuelve en el apuntador data los datos recuperados, la cadena
 * apuntada por key con la clave de la tupla y el tamaño en bytes de la tupla
 */

int sdbproceso_unpack( char *msg, unsigned int sz, char **key, tupla *data);


/** int MPI_timer (MPI_Request *request, MPI_Status *status)
 * función que verifica la llegada de un mensaje
 * si esta no ocurre después del valor TIEMPO (decimas de segundo)
 * el mensaje se descarta.Regresa 0 si el mensaje fue recibido
 * y 1 si la espera por el mensaje no fue exitosa
 */
int MPI_timer (MPI_Request *request, MPI_Status *status);

#endif /* SDBPROCESO_H_ */
