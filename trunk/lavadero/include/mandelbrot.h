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

typedef struct numero_complejo {

	double real;
	double imaginario;

} complex;

typedef struct pixel_mandelbrot{

	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;
	complex C;

} pixel;

typedef struct fila_matriz{

	double x, y, inc;
	int renglon, ancho;

} row;

/* void Dibuja_Mandelbrot();
 * Función que genera una imagen que representa el fractal de Mandelbrot y la almacena en una archivo
 * .ppm (Portable Pixel Map)
 */
void Dibuja_Mandelbrot();

/* void mandelbrot_Menu( int * ancho, int * alto, double * limx1, double * limx2, double * limy1, double * limy2 )
 * función que recibe del usuario el ancho y alto de la imagen, el dominio (limx1, limx2) y el rango (limy1, limy2)
 * sobre el cual se calculará el conjunto de Mandelbrot, así como el nombre con el que se guardará la imagen
 */
void mandelbrot_Menu( unsigned int * alto, unsigned int * ancho, double * limx1, double * limx2, double * limy1, double * limy2, char * nombre );


/* pixel ** mandelbrot_CreaMatrizPixel ( unsigned int alto, unsigned int ancho )
 * función que reserva memoria para crear una matriz de pixeles de mandelbrot, recibe el número de renglones (alto) y el número de columnas
 * (ancho) y regresa el apuntador de la matriz creada
 */
pixel ** mandelbrot_CreaMatrizPixel ( unsigned int alto, unsigned int ancho );

/* void mandelbrot_CalculaComplejos ( pixel * vector, unsigned int ancho, double limx1, double limy1, double incx)
 * función que llena el campo correspondiente al número complejo dependiendo el dominio, rango y tamaño de la imagen proporcionado por el usuario
 *
 */
void mandelbrot_CalculaComplejos ( pixel * vector, unsigned int ancho, double limx1, double limy1, double incx);

/* void mandelbrot_CalculaColor (pixel *vector, unsigned int ancho )
 * función que asigna color a un pixel dependiendo si esta o no en el conjunto de mandelbrot
 */
void mandelbrot_CalculaColor (pixel *vector, unsigned int ancho );

/* void mandelbrot_AsignaColor ( pixel * fractal, int cuenta )
 * asigna un color RGB al pixel apuntado por fractal, el color será rojo oscuro si el número está dentro del conjunto de Mandelbrot,
 * naranja si esta muy cerca del conjunto, amarillo si esta cerca y negro si no esta cerca
 *
 */
void mandelbrot_AsignaColor ( pixel * fractal, int cuenta, double distancia );

/* int mandelbrot_GuardarImagen( cadena nombre, pixel ** imagen, unsigned int alto, unsigned int ancho )
 * Función para guardar imagen en un archivo nombre.ppm (PORTABLE PIXEL MAP), se le agrega como cabecera
 * P3
 * # comentario
 * ancho alto
 * intensidad (0-255)
 */
int mandelbrot_GuardarImagen( cadena nombre, pixel ** imagen, unsigned int alto, unsigned int ancho );

/* void mandelbrot_DestruyeMatrizPixel( pixel ** imagen )
 * función para liberar la matriz creada apuntada por imagen
 */
void mandelbrot_DestruyeMatrizPixel( pixel ** imagen );

/* void mandelbrot_EnviaRenglones( unsigned int alto, unsigned int anchoIm, double x1, double x2, double y1, double y2 );
 * Función que envia renglones al espacio de tuplas para que los trabajdores puedan procesar los pixeles de
 * la imagen
 */
void mandelbrot_EnviaRenglones( unsigned int alto, unsigned int ancho, double x1, double x2, double y1, double y2 );

/* void mandelbrot_RecibeRenglones( pixel ** matriz, unsigned int  Alto, unsigned int Ancho );
 * Función que guarda en una matriz de tipo pixel los renglones procesados por un esclavo
 */
void mandelbrot_RecibeRenglones( pixel ** matriz, unsigned int  alto, unsigned int ancho );

/* void mandel_brot_CalculaRenglones();
 * Función que se encargar de calcular si los números complejos almacenados en un vector de pixeles forman parte del conjunto
 * de Mandelbrot, dependiendo del número asigna un color al vector
 */
void mandelbrot_CalculaRenglones();

/* void mandelbrot_Coordinador()
 * función coordinadora
 */
void mandelbrot_Coordinador();
#endif /* MANDELBROT_H_ */
