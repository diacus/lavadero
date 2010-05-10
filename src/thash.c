/*
 * thash.c
 *
 *  Created on: 10/05/2010
 *      Author: diacus
 */

#include <stdlib.h>
#include <thash.h>

unsigned int hash( char *s );

thash thash_get() {
	static int creada = 0;
	static thash th;
	if( !creada ) {
		th = (thash) calloc( SIZE, sizeof(int) );
		creada ++;
	}
	return th;
}

unsigned int hash( char *s ) {

}

/* int thash_in( char *key, int value )
 *
 * Inserta el valor value usado la clave key dentro
 * de la tabla de dispersión.
 */

int thash_in( char *key, int value );

/* int thash_out( char *key )
 *
 * Recupera el dato con la clave asociada key dentro de la
 * tabla de dispersión.
 */

int thash_out( char *key );

/* int thash_drop( char *key )
 *
 * Elimina de la tabla de dispersión el elemento con
 * clave key.
 */

int thash_drop( char *key );

/* int thash_flush()
 *
 * borra todos lo elementos almacenados en la
 * tabla de dispersión.
 */

int thash_flush();

/* int thash_delete()
 *
 * Libera el espacio de memoria que ocupa la tabla de
 * dispersión.
 */

int thash_delete();
