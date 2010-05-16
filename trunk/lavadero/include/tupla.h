/*
 * tupla.h
 *
 *  Created on: 05/05/2010
 *      Author: diacus
 */

#ifndef TUPLA_H_
#define TUPLA_H_

typedef void* item;
typedef item* tupla;

/* tupla *tupla_newd( unsigned int k, void *val )
 *
 */

tupla tupla_new_d( unsigned int N, ... );

/* tupla *tupla_newi( unsigned int k, void *val )
 *
 */

tupla tupla_new_i( unsigned int N, ... );

/* tupla *tupla_newi( unsigned int k, void *val )
 *
 */

tupla tupla_new_v( const char * types , ... );


/* int tupla_print( tupla *t )
 *
 */

int tupla_print( tupla *t );

/* int tupla_delete( tupla *t )
 *
 */
int tupla_delete( tupla *t );

int count_porcent(const char * s);

#endif /* TUPLA_H_ */
