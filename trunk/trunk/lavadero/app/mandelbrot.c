/*
 * mandelbrot.c
 *
 *  Created on: 26/05/2010
 *      Author: ryuuba
 */

#include <stdio.h>
#include <mandelbrot.h>
#include <stdlib.h>
#include <sdblinda.h>
#include <math.h>
#include <string.h>
#include <tupla.h>
#include <sdbespacio.h>

void Madelbrot_distribuido( int argc, char *argv[] ) {

	estado *edo;
	sdblinda_iniciar( argc, argv );
	edo = sdbproceso_estado();
	if ( SOYMAESTRO( edo ) )
		mandelbrot_Coordinador();
	else
		mandelbrot_CalculaRenglones();

	sdblinda_detener();
}

void mandelbrot_Coordinador(){

	unsigned int AnchoIm =11, AltoIm=11; /*dimensiones de la imagen*/
	double x1=-2, x2=2, y1=-2, y2=2; /*límites x1, x2 corresponden al dominio; y1, y2 al rango de la imagen*/
	pixel ** imagen;
	cadena nombre;
	tupla t;
	TUPLA_NEW( t, sizeof( unsigned int ) );
	/* mandelbrot_Menu( &AltoIm, &AnchoIm, &x1, &x2, &y1, &y2, nombre); */
	TUPLA_WRITE( t, &AnchoIm );
	sdblinda_meter( "ancho", t );
	printf("guarde ancho\n");
	/*
	imagen = mandelbrot_CreaMatrizPixel ( AltoIm, AnchoIm );

	mandelbrot_EnviaRenglones( AltoIm, AltoIm, x1, x2, y1, y2 );
	mandelbrot_RecibeRenglones( imagen, AltoIm, AnchoIm );
	mandelbrot_GuardarImagen( nombre, imagen, AltoIm, AnchoIm );
	mandelbrot_DestruyeMatrizPixel ( imagen );*/
}

void mandelbrot_CalculaRenglones( ){

	int bandera = 1;
	unsigned int ancho;
	tupla t1, t2, t3;
	row r;
	pixel *vector;
	TUPLA_NEW( t3, sizeof( unsigned int ) );
	sdblinda_leer( "ancho", t3 );
	TUPLA_READ ( &ancho, t3 );
	printf("ancho = % d\n", ancho);/*
	TUPLA_NEW( t1, sizeof( row ) );
	TUPLA_NEW( t2, sizeof( pixel) * ancho );
	vector = calloc( ancho, sizeof( pixel ) );

	while ( bandera ){
		sdblinda_sacar( t1, "renglon" );
		TUPLA_READ ( &r, t1 );
		if ( r.bandera ){
			mandelbrot_CalculaComplejos ( vector, ancho, r.x, r.y, r.inc );
			mandelbrot_CalculaColor ( vector, ancho );
			vector->ren = r.renglon;
			TUPLA_WRITE( t2, vector );
			sdblinda_meter( "renglonlisto", t2 );
		}
		else{
			r.bandera = 0;
			TUPLA_WRITE( t1, &r );
			sdblinda_meter( "renglon", t1 );
			bandera = 0;
		}
	}
	free ( vector );
	TUPLA_DELETE( t1 );
	TUPLA_DELETE( t2 );*/

}

void mandelbrot_Menu( unsigned int * alto, unsigned int * ancho, double * limx1, double * limx2, double * limy1, double * limy2, cadena nombre ){

	printf( "Programa generador de Fractal de Mandelbrot\n" );
	printf( "Dame las dimensiones de la imagen (alto, ancho)\n" );
	scanf( "%u%u", alto, ancho );
	printf( "Dame el dominio de la imagen ej(-2,2)\n");
	scanf( "%lf%lf", limx1, limx2 );
	printf( "Dame el rango de la imagen ej(-2,2)\n");
	scanf( "%lf%lf", limy1, limy2 );
	printf( "Nombre de la imagen: " );
	scanf( "%s", nombre );
	printf( "\n" );

}

pixel ** mandelbrot_CreaMatrizPixel ( unsigned int alto, unsigned int ancho ){

	pixel **ap, **apaux;
	int i;

	apaux = ( pixel ** )malloc( sizeof( pixel *) * ancho );
	ap = apaux;
	for( i = 0; i < alto ; i++ )
		apaux[i] = ( pixel * ) malloc ( sizeof( pixel ) * alto );
	if( ap == NULL )
		printf( "Memoria insuficiente\n" );

	return ap;

}

void mandelbrot_CalculaComplejos ( pixel * vector, unsigned int ancho, double limx1, double limy1, double incx){

	int i;

	for ( i = 0; i < ancho; i++){

		vector[i].C.real = limx1 + incx * i;
		vector[i].C.imaginario = limy1;
	}

}

void mandelbrot_CalculaColor (pixel *vector, unsigned int ancho ){

	int j, cuenta;
	double temp;
	complex Z;
	Z.real = 0.0; Z.imaginario = 0.0; cuenta = 0;
	for ( j = 0; j < ancho; j ++){
		  while ( (Z.real*Z.real + Z.imaginario*Z.imaginario) <= (4.0)  && cuenta < MAXITER ){
			  temp = Z.real*Z.real - Z.imaginario*Z.imaginario + vector[j].C.real;
			  Z.imaginario = 2*Z.real*Z.imaginario + vector[j].C.imaginario;
			  Z.real = temp;
			  cuenta ++;
			  }
			  mandelbrot_AsignaColor( &(vector[j]), cuenta, (Z.real*Z.real + Z.imaginario*Z.imaginario) );
			  Z.real = 0.0; Z.imaginario = 0.0; cuenta = 0;
		}

}

void mandelbrot_AsignaColor ( pixel * fractal, int cuenta, double distancia ){

	if( cuenta == 1000 ){
		fractal->rojo = 0; fractal->verde = 0; fractal->azul = 0; /* negro */
	}
	else if( cuenta < 1000 && distancia <= 4.1){
		fractal->rojo = 255; fractal->verde = 255; fractal->azul = 0; /* amarillo */
	}
	else if( cuenta < 1000 && distancia <= 4.15){
		fractal->rojo = 11; fractal->verde = 181; fractal->azul = 255; /* police strobe rgb(11, 181, 255) */
	}
	else if( cuenta < 1000 && distancia <= 4.2){
		fractal->rojo = 22; fractal->verde = 22; fractal->azul = 112; /* midnightblue(SVG) rgb(25, 25, 112 */
	}
	else if( cuenta < 1000 && distancia <= 4.4){
		fractal->rojo = 46; fractal->verde = 8; fractal->azul = 84; /* indigo rgb(46, 8, 84) */
	}

	else {
		fractal->rojo = 102; fractal->verde = 1; fractal->azul = 152; /* concord grape rgb(102, 1, 152) */
		}
}

int mandelbrot_GuardarImagen( cadena nombre, pixel ** imagen, unsigned int alto, unsigned int ancho ){
	FILE *fichero;
	int i,j;

	strcat(nombre, ".ppm");
	if ( ( fichero = fopen ( nombre, "w" ) ) == NULL ){
		printf( "No se puede abrir archivo %s\n" ,nombre );
		return 1;
	}

	fprintf ( fichero, "P3\n# Fractal de Mandelbrot SDB\n%u %u\n255\n", ancho, alto );

	for( i = 0; i < alto; i++ ){
		for( j = 0; j < ancho; j++ )
			fprintf( fichero, "%d %d %d ", imagen[i][j].rojo, imagen[i][j].verde, imagen[i][j].azul );
		fprintf( fichero, "\n" );
	}

	if( !fclose(fichero) )
		fprintf( stdout, "Datos guardados en el fichero: %s\n", nombre );
	else{
	      printf( "Error: fichero NO CERRADO\n" );
	      return 1;
	   }

	   return 0;

}

void mandelbrot_DestruyeMatrizPixel( pixel ** imagen ){

	free ( imagen );

}

void mandelbrot_EnviaRenglones( unsigned int alto, unsigned int ancho, double limx1, double limx2, double limy1, double limy2 ){

	int i, tam;
	row datos_renglon; /* [ x1, y1, ancho, incx] */
	double incx, decy;
	tupla fila;

	tam = sizeof( row );
	TUPLA_NEW( fila, tam );
	incx = fabs( limx2 - limx1 ) / ( alto - 1 );
	decy = fabs( limy2 - limy1 ) / ( ancho - 1 );
	datos_renglon.x = limx1;
	datos_renglon.inc = incx;
	datos_renglon.bandera = 1;

	for ( i = 0; i < alto; i ++){

		datos_renglon.renglon = i;
		datos_renglon.y = limy2 - decy * i;
		TUPLA_WRITE( fila, &datos_renglon );
		sdblinda_meter( "renglon", fila );

	}
	TUPLA_DELETE( fila );

}

void mandelbrot_RecibeRenglones( pixel ** matriz, unsigned int  alto, unsigned int ancho ){

	int i;
	pixel *vector = calloc( ancho, sizeof ( pixel ) );
	pixel ** aux = matriz;
	tupla t;
	cadena clave = "renglonlisto";
	row datos;

	TUPLA_NEW( t, sizeof( pixel ) * ancho );
	for ( i = 0; i < alto; i++ ){

		sdblinda_sacar( t, clave );
		TUPLA_READ( vector, t );
		memcpy ( aux + ancho * (vector->ren), vector, TUPLA_BYTES ( t ) );
		aux = matriz;

	}


	TUPLA_DELETE( t );
	TUPLA_NEW( t, sizeof( row ) );
	datos.bandera = 0;
	TUPLA_WRITE( t, &datos );
	sdblinda_meter( "renglon", t );
	TUPLA_DELETE( t );

}
