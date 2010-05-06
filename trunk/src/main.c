/*
 * main.c
 *
 *  Created on: 05/05/2010
 *      Author: diacus
 */

#include <tupla.c>

int main(int argc, char *argv[]) {
	char a = 'a';
	tupla *t = tupla_new(0, (void *) &a);
	print_tupla(t);
	tupla_delete(t);
	return 0;
}
