/*
 * main.c
 *
 *  Created on: 05/05/2010
 *      Author: diacus
 */

#include <tupla.h>
#include <prueba.h>

int main(int argc, char *argv[]) {
	char a = 'a';
	tupla *t = tupla_new(0, (void *) &a);
	tupla_print(t);
	tupla_delete(t);

	prueba1();
	/*pruebaN();*/

	return 0;
}
