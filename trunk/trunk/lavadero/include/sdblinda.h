/*
 * sdblinda.h
 *
 *  Created on: 14/05/2010
 *      Author: diacus
 */

#ifndef SDBLINDA_H_
#define SDBLINDA_H_


/* int sdblinda_start( int argc, char *argv[] )
 *
 * Función para inicializar el espacio de tuplas
 */

int sdblinda_start( int argc, char *argv[] );

/* int sdblinda_store( void *data, unsigned int size, const char *key )
 *
 * Función para almacenar los size bytes de datos apuntados por data, bajo
 * la clave key.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_store( void *data, unsigned int size, char *key );

/* int sdblinda_grab( void **data, char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función elimina los datos
 * del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_grab( void **data, char *key );

/* int sdblinda_drop( const char *key )
 *
 * Función para eliminar los datos guardados bajo la clave key almacenados en el
 * espacio de tuplas. Una vez borrados los datos, no se recuperarán.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_drop( char *key );

/* int sdblinda_read( void **data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función es parecida a sdblinda_grab,
 * sólo que NO elimina los datos del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_read( void **data, char *key );


/* int sdblinda_stop()
 *
 * Una vez terminada la aplicación, esta función destruye el espacio
 * de tuplas.
 */

int sdblinda_stop();

#endif /* SDBLINDA_H_ */
