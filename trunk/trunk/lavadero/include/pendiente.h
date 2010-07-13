/*
 * pendiente.h
 *
 *  Created on: 27/05/2010
 *      Author: diacus
 */

/**
 * @file
 * @author Giovanni Medrano <ryubba@gmail.com>
 * @author Diego Guzmán <dr.guzsant@gmail.com>
 *
 * @version 1.0
 *
 * @section Descripción
 *
 * Declaración del tipo de dato abstracto pendiente el cual
 * representa una petición que no ha sido atendida.
 */

#ifndef PENDIENTE_H_
#define PENDIENTE_H_


/** @typedef pendiente
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


/** NEWPENDIENTE(x)
 *
 * Macro para crear un nuevo registro de solicitudes
 * pendientes.
 *
 * Requiere que el parámetro sea un apuntador a pendiente.
 */

#define NEWPENDIENTE(x) x = (pendiente *) malloc(sizeof(pendiente))

/** DELETEPENDIENTE(x)
 *
 * Macro para liberar el espacio de memoria ocupado
 * por un pendiente.
 *
 * Requiere que el parámetro sea un apuntador a pendiente.
 */

#define DELETEPENDIENTE(x) free(x)


#endif /* PENDIENTE_H_ */
