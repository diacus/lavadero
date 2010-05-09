/*
 * tupla.h
 *
 *  Created on: 05/05/2010
 *      Author: diacus
 */

#ifndef TUPLA_H_
#define TUPLA_H_

typedef struct tp{
	unsigned int clave;
	void *valor;
} tupla;

/* tupla *tupla_new( unsigned int k, void *val )
 *
 */

tupla *tupla_new( unsigned int k, void *val );

/* int tupla_print( tupla *t )
 *
 */

int tupla_print( tupla *t );

/* int tupla_delete( tupla *t )
 *
 */
int tupla_delete( tupla *t );

#endif /* TUPLA_H_ */
