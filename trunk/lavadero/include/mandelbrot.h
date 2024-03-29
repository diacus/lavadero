/*
 * mandelbrot.h
 *
 *  Created on: 26/05/2010
 *      Author: ryuuba
 */

#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#define MAXITER 1000

typedef char cadena[25];

/**
 * @typedef numero_complejo
 *
 * Tipo de dato abstracto que representa un número complejo
 */

typedef struct numero_complejo {

	double real;
	double imaginario;

} complex;

/**
 * @typedef pixel_mandelbrot
 *
 * Tipo de dato abstracto que representa un pixel en la imagen
 * resultante del fractal de Mandelbrot
 */

typedef struct pixel_mandelbrot{

	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;
	complex C;

} pixel;

/**
 * @typedef pixel_mandelbrot
 *
 * Tipo de dato abstracto que representa un pixel en la imagen
 * resultante del fractal de Mandelbrot
 */

typedef struct fila_matriz{

	double x, y, inc;
	int renglon, ancho;

} row;

/**
 * Función que genera una imagen que representa el fractal de Mandelbrot de manera distribuida y la almacena en una archivo
 * .ppm (Portable Pixel Map)
 */

void mandelbrot_Distribuido( int argc, char *argv[] );

/**
 * Función encargada de obtener la información suficiente ( ancho de la imagen, x1, y1, inc ), para que los esclavos puedan generar
 * un renglon de la matriz que se empleará para almacenar los datos del fractal
 */
void mandelbrot_Coordinador();

/**
 * Función que se encargar de llenar los datos del fractal correspondientes a un renglon de la matriz
 */
void mandelbrot_CalculaRenglones();

/**
 * Función con la que se obtiene del usuario los datos necesarios para generar el fractal
 */
void mandelbrot_Menu( unsigned int * alto, unsigned int * ancho, double * limx1, double * limx2, double * limy1, double * limy2, cadena nombre );

/**
 * Función para reservar memoria para almacenar la matriz
 */
pixel ** mandelbrot_CreaMatrizPixel ( unsigned int alto, unsigned int ancho );

/**
 * Función que calcula las coordenadas del plano complejo correspondientes a la dimensión que el usuario proporcionó
 */
void mandelbrot_CalculaComplejos ( pixel * vector, unsigned int ancho, double limx1, double limy1, double incx);

/**
 * Función con la que se calcula si un punto del plano complejo corresponde al conjunto de Mandelbrot y dependiendo de
 * la distancia y el numero de iteraciones asigna el color a la imagen
 */
void mandelbrot_CalculaColor (pixel *vector, unsigned int ancho );

/**
 * Función que llena el campo correspondiente al color en la imagen
 */
void mandelbrot_AsignaColor ( pixel * fractal, int cuenta, double distancia );

/**
 * Funcion con la que se guarda en un archivo .ppm la imagen del fractal generada
 */
int mandelbrot_GuardarImagen( cadena nombre, pixel ** imagen, unsigned int alto, unsigned int ancho );

/**
 * Función que libera el espacio de memoria reservado para manipular la matriz de pixeles
 */
void mandelbrot_DestruyeMatrizPixel( pixel ** imagen );

/**
 * Función empleada por el coordinador para enviar al espacio de tuplas los renglones a calcular
 */
void mandelbrot_EnviaRenglones( unsigned int alto, unsigned int ancho, double limx1, double limx2, double limy1, double limy2 );

/**
 *
 */
void mandelbrot_RecibeRenglones( pixel ** matriz, unsigned int  alto, unsigned int ancho );

/**
 *
 */
void mandelbrot_ImprimeVector ( pixel * vector, unsigned int ancho );
#endif /* MANDELBROT_H_ */
