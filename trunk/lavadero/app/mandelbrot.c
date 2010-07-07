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

void mandelbrot_Distribuido( int argc, char *argv[] ) {

	estado *edo;
	sdblinda_iniciar( argc, argv );
	edo = sdbproceso_estado();
	if ( SOYMAESTRO( edo ) )
		mandelbrot_Coordinador();
	else if( SOYESCLAVO( edo ))
		mandelbrot_CalculaRenglones();

	sdblinda_detener();
}

void mandelbrot_Coordinador(){

	unsigned int AnchoIm =2000, AltoIm=2000; /*dimensiones de la imagen*/
	double x1=-2.3, x2=2.3, y1=-2.3, y2=2.3; /*límites x1, x2 corresponden al dominio; y1, y2 al rango de la imagen*/
	pixel ** imagen;
	cadena nombre = "fractal";
	/* mandelbrot_Menu( &AltoIm, &AnchoIm, &x1, &x2, &y1, &y2, nombre); */
	imagen = mandelbrot_CreaMatrizPixel ( AltoIm, AnchoIm );
	mandelbrot_EnviaRenglones( AltoIm, AltoIm, x1, x2, y1, y2 );
	mandelbrot_RecibeRenglones( imagen, AltoIm, AnchoIm );
	mandelbrot_GuardarImagen( nombre, imagen, AltoIm, AnchoIm );
	mandelbrot_DestruyeMatrizPixel ( imagen );
}


void mandelbrot_Menu( unsigned int * alto, unsigned int * ancho, double * limx1, double * limx2, double * limy1, double * limy2, cadena nombre ){

	int tmp;
	printf( "Programa generador de Fractal de Mandelbrot\n" );
	printf( "Dame las dimensiones de la imagen (alto, ancho)\n" );
	tmp = scanf( "%u%u", alto, ancho );
	printf( "Dame el dominio de la imagen ej(-2,2)\n");
	tmp = scanf( "%lf%lf", limx1, limx2 );
	printf( "Dame el rango de la imagen ej(-2,2)\n");
	tmp = scanf( "%lf%lf", limy1, limy2 );
	printf( "Nombre de la imagen: " );
	tmp = scanf( "%s", nombre );
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
		fprintf( stderr, "Memoria insuficiente\n" );

	return ap;

}

void mandelbrot_EnviaRenglones( unsigned int alto, unsigned int ancho, double limx1, double limx2, double limy1, double limy2 ){

	int i;
	row datos_renglon; /* [ x1, y1, ancho, incx] */
	double incx, decy;
	tupla fila;

	TUPLA_NEW( fila, sizeof(row) );

	incx = fabs( limx2 - limx1 ) / ( alto - 1 );
	decy = fabs( limy2 - limy1 ) / ( ancho - 1 );

	datos_renglon.x = limx1;
	datos_renglon.ancho = ancho;
	datos_renglon.inc = incx;

	for ( i = 0; i < alto; i ++){

		datos_renglon.renglon = i;
		datos_renglon.y = limy2 - decy * i;
		TUPLA_WRITE( fila, &datos_renglon );
		sdblinda_meter( "renglon", fila );

	}
	TUPLA_DELETE( fila );

}

void mandelbrot_RecibeRenglones( pixel ** matriz, unsigned int  alto, unsigned int ancho ){

	int i, j, renglon;
	tupla t;
	row datos;
	char *paquete = ( char * )malloc( ancho * sizeof( pixel ) + sizeof( int ) );
	pixel *vector;

	TUPLA_NEW( t, sizeof( pixel ) * ancho + sizeof( int ) );
	for ( i = 0; i < alto; i++ ){

		sdblinda_sacar( "renglonlisto", t );
		TUPLA_READ( paquete, t );
		renglon = *( int *) paquete;
		vector = (pixel *)(paquete + sizeof( int ));
		for ( j = 0; j < ancho; j++){
			matriz[renglon][j].rojo = vector[j].rojo;
			matriz[renglon][j].verde = vector[j].verde;
			matriz[renglon][j].azul = vector[j].azul;
			matriz[renglon][j].C.real = vector[j].C.real;
			matriz[renglon][j].C.imaginario = vector[j].C.imaginario;
		}


	}

	free ( paquete );
	TUPLA_DELETE( t );
	TUPLA_NEW( t, sizeof( row ) );
	datos.inc = 0;
	TUPLA_WRITE( t, &datos );
	sdblinda_meter( "renglon", t );
	TUPLA_DELETE( t );

}

void mandelbrot_CalculaRenglones( ){

	int bandera = 1;
	tupla t1 = NULL, t2 = NULL;
	row fila;
	pixel *vector = NULL;
	char *paquete = NULL;
	TUPLA_NEW( t1, sizeof( row ) );

	while ( bandera ){
		sdblinda_sacar( "renglon", t1 );
		TUPLA_READ ( &fila, t1 );
		if( vector == NULL){
			vector = calloc( fila.ancho, sizeof( pixel ) );
			/*paquete = calloc( fila.ancho * sizeof( pixel ) + sizeof(int), sizeof(char) );*/
			paquete = ( char * )malloc( fila.ancho * sizeof( pixel ) + sizeof( int ) );
			TUPLA_NEW( t2, sizeof( pixel ) * fila.ancho + sizeof( int ));
		}
		if ( fila.inc ){
			mandelbrot_CalculaComplejos ( vector, fila.ancho, fila.x, fila.y, fila.inc );
			mandelbrot_CalculaColor ( vector, fila.ancho );
			*(int *) paquete = fila.renglon;
			memcpy ( paquete + sizeof(int), vector, fila.ancho * sizeof( pixel ) );
			TUPLA_WRITE( t2, paquete );
			sdblinda_meter( "renglonlisto", t2 );
		}
		else{
			sdblinda_meter( "renglon", t1 );
			bandera = 0;
		}
	}
	free ( paquete );
	free ( vector );
	TUPLA_DELETE( t1 );
	TUPLA_DELETE( t2 );

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
		fprintf( stderr, "No se puede abrir archivo %s\n" ,nombre );
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


void mandelbrot_ImprimeVector ( pixel * vector, unsigned int ancho ){
	int i;

	for( i = 0; i < ancho; i++){
		printf( "vector[%d] -> rojo = %i, verde = %i, azul = %i, real = %f, im = %f\n",
				i,
				vector[i].rojo,
				vector[i].verde,
				vector[i].azul,
				vector[i].C.real,
				vector[i].C.imaginario);
	}


}
