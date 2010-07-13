/**
 * @file
 * @author Giovanni Medrano <ryubba@gmail.com>
 * @author Diego Guzmán <dr.guzsant@gmail.com>
 *
 * @version 1.0
 *
 * @section Descripción
 *
 * Este programa genera un Fractal de Mandelbrot de manera distribuida
 * utilizando una implementación de la memoria virtual distribuida
 * linda.
 */

#include <mandelbrot.h>
#include <prueba.h>

int main( int argc, char *argv[] ) {

	mandelbrot_Distribuido( argc, argv );
	/*prueba(argc, argv);*/

	/* return prueba_pthread( argc, argv ); */
	return 0;
}
