/*
 * sdbesclavo.h
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#ifndef SDBESCLAVO_H_
#define SDBESCLAVO_H_

#include <sdblinda.h>

void *sdbesclavo_pack( void *data, unsigned int sz, char *key);

/* int suma( int *col1, int *col2, unsigned int size )
 *
 */

double *suma( double *col1, double *col2, unsigned int size );

int esclavo_listen();

#endif /* SDBESCLAVO_H_ */
