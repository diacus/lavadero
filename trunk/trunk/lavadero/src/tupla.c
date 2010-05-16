/*
 * tupla.c
 *
 *  Created on: 05/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <tupla.h>



int count_porcent(const char * s){
	int acum=0;
	while(*s != '\0'){
		if (*s == '%')
			acum ++;
		s++;
    }
	return acum;
}

/* tupla *tupla_new( unsigned int k, void *val )
 *
 */

tupla tupla_new_i( unsigned int N, ... ) {
	item elemento;
	tupla res = (tupla) calloc( N , sizeof(item) );
	int i, *val;
	va_list args;
	va_start(args, N);
	for (i=0; i< N; i++){
		val = (int*) malloc (sizeof(int));
		*val = va_arg(args, int);
		elemento = val;
		res[i] = elemento;
	}
	va_end(args);
	return res;
}

tupla tupla_new_d( unsigned int N, ... ) {
	item elemento;
	tupla res = (tupla) calloc( N , sizeof(item) );
	int i;
	double *val;
	va_list args;
	va_start(args, N);
	for (i=0; i< N; i++){
		val = (double*) malloc (sizeof(double));
		*val = va_arg(args, double);
		elemento = val;
		res[i] = elemento;
	}
	va_end(args);
	return res;
}

tupla tupla_new_v(const char * types , ... ) {
	const char *p = types;
	item elemento;
	tupla res;
	int i=0, *vint, datos;
	double *vdouble;
	/* float *vfloat; */
	char *vstring;
	datos = count_porcent(p);
	res = (tupla) calloc( datos+1 , sizeof(item) );
	va_list args;
	va_start(args, types);
	for(p = types ; *p != '\0'; p++){
		if(*p=='%')
			continue;
		else if (*p=='l'){
			p++;
			continue;
		}
		else if(*p=='d'){
			vint = (int*) malloc (sizeof(int));
			*vint = va_arg(args, int);
			elemento = vint;
			res[i] = elemento;
		}
		else if (*p=='f'){
			vdouble = (double*) malloc (sizeof(double));
			*vdouble = va_arg(args, double);
			elemento = vdouble;
			res[i] = elemento;
		}
		else if (*p == 'c'){
			vint = (int*) malloc (sizeof(int));
			*vint = va_arg(args, int);
			elemento = vint;
			res[i] = elemento;
		}
		else if (*p == 's'){
			vstring = (char*) malloc (sizeof(char *));
			vstring = va_arg(args, char *);
			elemento = vstring;
			res[i] = elemento;
		}
		else
			printf("Especificador de tipo desconocido\n");
		i++;
	}
	elemento = types;
	res[i] = elemento;
	va_end(args);
	return res;
}

/* int tupla_print( tupla *t )
 *
 */

int tupla_print( tupla *t ) {
	//printf( "(%u,%X)\n", t->clave, (unsigned int) t->valor );
	return 0;
}

/* int tupla_delete( tupla *t )
 *
 */

int tupla_delete( tupla *t ) {
	free(t);
	return 0;
}
