/*
 * prueba.h
 *
 *  Created on: 06/05/2010
 *      Author: diacus
 */

#ifndef PRUEBA_H_
#define PRUEBA_H_

int prueba1();

/* int pruebalista( int argc, char *argv[] )
 *
 * Función para probar la lista
 */

int pruebalista( int argc, char *argv[] );

/* int pruebahash( int argc, char *argv[] )
 *
 * Función para probar la tabla hash
 */

int pruebahash( int argc, char *argv[] );

int pruebabit();

/* Funciones generadas por Eclipse PTP al crear un
 * MPI Project.
 */

void calc_pi(int rank, int num_procs);
int CalculaPI(int argc, char *argv[]);

int pruebapack();
int prueba_linda( int argc, char *argv[] );

#endif /* PRUEBA_H_ */
