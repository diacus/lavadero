/*
 * main.c
 *
 *  Created on: 05/05/2010
 *      Author: diacus
 */

#include <mandelbrot.h>
#include <prueba.h>

int main( int argc, char *argv[] ) {

	mandelbrot_Distribuido( argc, argv );
	/*prueba(argc, argv);*/

	/* return prueba_pthread( argc, argv ); */
	return 0;
}
