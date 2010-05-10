/*
 * thash.h
 *
 *  Created on: 10/05/2010
 *      Author: diacus
 */

#ifndef THASH_H_
#define THASH_H_

#define SIZE 1024

typedef int *thash;

/* thash thash_get()
 *
 * función constructora, que se asegura de que exista una
 * y sólo una tabla de dispersión.
 *
 */
thash thash_get();

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

#endif /* THASH_H_ */
