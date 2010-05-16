/*
 * sdblinda.c
 *
 *  Created on: 15/05/2010
 *      Author: diacus
 */

#include <sdblinda.h>
#include <sdbmaestro.h>
#include <sdbesclavo.h>

/* int sdblinda_store( void *data, unsigned int size, const char *key )
 *
 * Función para almacenar los size bytes de datos apuntados por data, bajo
 * la clave key.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_store( void *data, unsigned int size, const char *key ) {
	return 0;
}

/* int sdblinda_grab( void *data, const char *key )
 *
 * Función para recuperar los datos almacenados bajo la clave key, y recibirlos
 * en el espacio de memoria apuntado por data.  Esta función elimina los datos
 * del espacio de tuplas.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_grab( void *data, const char *key ) {
	return 0;
}

/* int sdblinda_drop( const char *key )
 *
 * Función para eliminar los datos guardados bajo la clave key almacenados en el
 * espacio de tuplas. Una vez borrados los datos, no se recuperarán.
 *
 * El valor de retorno le notifica al programador acerca del éxito o fracaso
 * de la operación.
 */

int sdblinda_drop( const char *key ) {
	return 0;
}
