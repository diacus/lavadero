/*
 * sdbproceso.h
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#ifndef SDBPROCESO_H_
#define SDBPROCESO_H_

#include <mpi.h>

/* Registro: estado
 *
 * Estructura para almacenar las variables que identifican
 * a cada proceso dentro de MPI.
 */

typedef struct edo {
	int			my_rank;		/* rank of process */
	int			num_procs;		/* number of processes */
	int			source;			/* rank of sender */
	int			dest;    		/* rank of receiver */
	int			tag;    		/* tag for messages */
	char		*message;   	/* storage for message */
	MPI_Status	status ;		/* return status for receive */
} estado;

/* char *sdblinda_pack( unsigned int *nbytes, void *data, unsigned int *sz, char *key )
 *
 * Función para empaquetar los *sz bytes apuntados por data y su
 * clave key, en una sola porción de memoria, para ser enviados
 * a la memoria compartida.
 *
 * La función devuelve un apuntador al espacio de memoria que
 * almacena el "paquete" y escribe en el entero apuntado por
 * nbytes el tamaño de este.
 */

char *sdbproceso_pack( unsigned int *nbytes, void *data, unsigned int *sz, char *key );

/* void *sdbproceso_unpack( unsigned int *nbytes, char **key, char *msg )
 *
 * Función para descomponer el mensaje apuntado por msg.
 *
 * Devuelve un apuntador a los datos recuperados, escribe en el entero
 * apuntado por nbytes el tamaño en bytes de dichos datos y en la cadena
 * apuntada por key la clave con que se etiqueta.
 */

void *sdbproceso_unpack( unsigned int *nbytes, char* key, char *msg );

#endif /* SDBPROCESO_H_ */
