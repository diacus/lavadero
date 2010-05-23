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
#define ENVIA    100 /* Etiqueta para un mensaje que envía una tupla para que se almacene. */
#define SOLICITA 101 /* Etiqueta para un mensaje de solicitud de tupla.                    */
#define RETIRA   102 /* Etiqueta para un mensaje que busca eliminar una tupla del espacio. */
#define ELIMINA	 103 /* Etiqueta para un mensaje que busca eliminar una tupla del espacio. */
#define TALLA	 104 /* Etiqueta para un mensaje que transmite el tamaño de un dato.       */
#define DATO	 105 /* Etiqueta para un mensaje que transmite una tupla.                  */
#define INICIO   106 /* Etiqueta inicial.                                                  */
#define FIN      107 /* Etiqueta final.                                                    */

#define SOYMAESTRO(e) !(e->my_rank)

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

/* char *sdbproceso_pack( unsigned int *nbytes, void *data, unsigned int sz, char *key )
 *
 * Función para empaquetar los *sz bytes apuntados por data y su
 * clave key, en una sola porción de memoria, para ser enviados
 * a la memoria compartida.
 *
 * La función devuelve un apuntador al espacio de memoria que
 * almacena el "paquete" y escribe en el entero apuntado por
 * nbytes el tamaño de este.
 */

char *sdbproceso_pack( unsigned int *nbytes, void *data, unsigned int sz, char *key );

/* int sdbproceso_unpack( void *data, unsigned int *nbytes, char **key, char *msg )
 *
 * Función para descomponer el mensaje apuntado por msg.
 *
 * Devuelve en el apuntador data los datos recuperados, escribe en el entero
 * apuntado por nbytes el tamaño en bytes de dichos datos y en la cadena
 * apuntada por key la clave con que se etiqueta.
 */

int sdbproceso_unpack( void *data, unsigned int *nbytes, char **key, char *msg );


/* int cpy_tupla (void * or, unsigned int size, void ** de)
 *
 * función para copiar una tupla recibida del espacio a una variable local
 *
 * Devuelve la tupla destino ( ** de) inicializada con respecto al tamaño (size)
 * de la tupla origen (* or)
 *
 */
int cpy_tupla (void * or, unsigned int size, void ** de);

#endif /* SDBPROCESO_H_ */
