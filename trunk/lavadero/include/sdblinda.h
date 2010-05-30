/*
 * sdblinda.h
 *
 *  Created on: 14/05/2010
 *      Author: diacus
 */

#ifndef SDBLINDA_H_
#define SDBLINDA_H_

#include <tupla.h>

/* int sdblinda_iniciar( int argc, char *argv[] )
 *
 * Función para inicializar el espacio de tuplas
 */

int sdblinda_iniciar( int argc, char *argv[] );

/* int sdblinda_meter( char *key, tupla data )
 *
 * Función para almacenar los la tupla data, bajo
 * la clave key, en el espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_meter( char *key, tupla data );

/* int sdblinda_sacar( void **data, char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en la tupla data.  Esta función elimina los datos del espacio de tuplas.
 *
 * Si la tupla etiquetada con la clave key, no se encuentra en la memoria
 * compartida, el proceso que la solicitó se queda bloqueado hasta que esté
 * disponible.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_sacar( char *key, tupla data );

/* int sdblinda_suprimir( const char *key )
 *
 * Función para eliminar los datos guardados bajo la clave key almacenados en el
 * espacio de tuplas. Una vez borrados los datos, no se recuperarán.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_suprimir( char *key );

/* int sdblinda_leer( tupla data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en la tupla data.  Esta función es parecida a sdblinda_sacar, sólo que NO
 * elimina los datos del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_leer( tupla data, char *key );


/* int sdblinda_detener()
 *
 * Una vez terminada la aplicación, esta función destruye el espacio
 * de tuplas.
 */

int sdblinda_detener();

#endif /* SDBLINDA_H_ */
