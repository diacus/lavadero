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

#define LINDA      0 /* Identificador del proceso que administra el espacio de tuplas.     */
#define STORE    100 /* Etiqueta para un mensaje que envía una tupla para que se almacene. */
#define GRAB     101 /* Etiqueta para un mensaje de solicitud de tupla.                    */
#define READ     102 /* Etiqueta para un mensaje que busca eliminar una tupla del espacio. */
#define DROP   	 103 /* Etiqueta para un mensaje que busca eliminar una tupla del espacio. */
#define SIZE     104 /* Etiqueta para un mensaje que transmite el tamaño de un dato.       */
#define DATA	 105 /* Etiqueta para un mensaje que transmite una tupla.                  */
#define BEGIN    106 /* Etiqueta inicial.                                                  */
#define END      107 /* Etiqueta final.                                                    */

#define SOYESPACIO(e) !(e->my_rank)

/* Registro: estado
 *
 * Estructura para almacenar las variables que identifican
 * a cada proceso dentro de MPI.
 */

typedef struct edo {
	int			my_rank;		/* Identificador de proceso                */
	int			num_procs;		/* Número de procesos activos              */
	int			source;			/* Identificador del proceso emisor        */
	int			dest;    		/* Identificador del proceso destino       */
	int			tag;    		/* Etiqueta para el mensaje                */
	char		*message;   	/* Apuntador al mensaje a enviar o recibir */
	MPI_Status	status ;		/* Estado de la comunicación               */
} estado;

/* estado *sdbproceso_estado()
 *
 * Función para crear las variables de estado del proceso
 * y obtener un apuntador al registro donde se alojan.
 *
 * Devuelve un apuntador a una variable de tipo estado
 */
estado *sdbproceso_estado();

/* char *sdbproceso_pack( void *data, unsigned int sz, char *key )
 *
 * Función para empaquetar los sz bytes apuntados por data y su
 * clave key, en una sola porción de memoria, para ser enviados
 * a la memoria compartida.
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

char *sdbproceso_pack( void *data, unsigned int sz, char *key );

/* int sdbproceso_unpack( char *msg, unsigned int sz, char **key, void **data)
 *
 * Función para descomponer el mensaje apuntado por msg de tamaño sz.
 *
 * Devuelve en el apuntador data los datos recuperados, la cadena
 * apuntada por key con la clave de la tupla y el tamaño en bytes de la tupla
 */

int sdbproceso_unpack( char *msg, unsigned int sz, char **key, void **data);



#endif /* SDBPROCESO_H_ */
