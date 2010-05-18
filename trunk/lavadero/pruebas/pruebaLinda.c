/*
 * pruebaLinda.c
 *
 *  Created on: 18/05/2010
 *      Author: diacus
 */

#include <prueba.h>
#include <sdbproceso.h>
#include <sdblinda.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prueba_linda( int argc, char *argv[] ) {

	estado *edo = sdbproceso_estado();
	sdblinda_start( argc, argv );

	if( SOYMAESTRO(edo) ) {
		printf("Soy un proceso maestro\n");
	} else {
		printf("Soy el proceso esclavo numero %d\n", edo->my_rank );
	}

	sdblinda_stop();
	return 0;
}
