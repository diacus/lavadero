/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <stdio.h>
#include <sdbespacio.h>
#include <stdlib.h>

/* thash *sdbespacio_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbespacio_gethash() {
	static int creadaHash = 0;
	static thash *tabla = NULL;

	if( ! creadaHash ) {
		creadaHash ++;
		/* Esta parte puede ser parametrizada con */
		/* un archivo de configuración            */
		tabla = thash_new(TABLESIZE);
	}

	return tabla;
}


/* thash *sdbespacio_getpendientes()
 *
 * Funcipon para obtener una referencia al espacio en el que
 * se van a almacenar las peticiones pendientes.
 */

thash *sdbespacio_getpendientes() {

	static int creadaPendientes = 0;
	static thash *pendientes = NULL;


	if( ! creadaPendientes ) {
		creadaPendientes ++;
		/* Esta parte puede ser parametrizada con */
		/* un archivo de configuración            */
		pendientes = thash_new(TABLESIZE);
	}

	return pendientes;
}

/* int sdbmaestro_iniciar()
 *
 * Función para inicializar el especio de tuplas.
 */

int sdbespacio_iniciar() {

	/* thash *tabla = sdbespacio_gethash(); / * apuntador a tabla hash */
	estado *edo = sdbproceso_estado(); /* apuntador a estado (propio de LINDA) */
	char *buffer; /* buffer de mensaje a recibir */
	int n = edo -> num_procs - 1; /* número de procesos activos al momento de iniciar la comunicación */
	int nbytes;
	int source, tag; /* tamaño (nbytes) del buffer a recibir, identidad (source) del emisor y
	etiqueta (tag) del mensaje */


	printf("hay %d procesos \n", n);
	while( n > 0 ) {


		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &(edo->status));
		source = (edo->status).MPI_SOURCE;
		tag = (edo->status).MPI_TAG;
		MPI_Get_count(&(edo->status), MPI_BYTE, &nbytes);
		printf("SERVER: bytes a recibir = %d, from %d\n", nbytes, source);
		buffer = (char *) calloc( nbytes, sizeof(char) );
		MPI_Recv( buffer, nbytes, MPI_BYTE, source, tag, MPI_COMM_WORLD, &(edo->status) );

		switch(tag){

		case END :
			printf("SERVER: Recibi mensaje FIN de proc %d\n", source);
			n--;
			break;

		case STORE :
			printf("SERVER: Recibi mensaje STORE de proc %d\n", source);
			sdbespacio_atiendeMeter( buffer, nbytes );
			break;

		case GRAB :
			printf("SERVER: Recibi mensaje GRAB de proc %d\n", source);
			/* int sdbespacio_atiendeSacar( char *key, unsigned int src )*/
			sdbespacio_atiendeSacar( buffer, source);
			break;

		case READ :
			printf("SERVER: Recibi mensaje READ de proc %d para leer clave %s\n", source, buffer);
			/* int sdbespacio_atiendeLeer( char *key, unsigned int src ) */
			sdbespacio_atiendeLeer( buffer, source );
			break;

		case DROP :
			printf("SERVER: Recibi mensaje DROP de proc %d para borrar tupla con clave %s\n", source, buffer);
			/* int sdbespacio_atiendeSuprimir( char *key )*/
			sdbespacio_atiendeSuprimir ( buffer );
			break;

		default:
			n=0;
			printf("Error de aplicación terminando\n");

		}

	}
	/*thash_delete( sdbespacio_gethash() );
	thash_delete( sdbespacio_getpendientes() );*/
	return 0;
}


/* unsigned int sdbespacio_atiendeMeter( char * message, int sz )
 *
 * Función que recibe un mensaje y el tamaño en bytes de éste
 * almacena en la tabla hash la tupla contenida en el mensaje
 * empleando la clave también empaquetada en el mensaje
 *
 */
unsigned int sdbespacio_atiendeMeter( char * message, int sz ){

	thash        *tabla, *poratender;	/* Creación de apuntador a la tabla hash de indices y tabla de pendientes*/
	pendiente    *p;					/* apuntador a la estructura pendiente */
	void         *data;					/* Tupla a almacenar */
	char         *key;					/* Clave de la tupla */
	int          indice, tam;			/* índice de la tabla en el que se almacenará la tupla y tamaño de la tupla*/
	unsigned int size;

	tam    = sdbproceso_unpack( message, sz, &key, &data);
	tabla  = sdbespacio_gethash();
	indice = thash_insert( tabla, data, tam, key);


	/* Revisando el tabla de pendiente*/
	poratender = sdbespacio_getpendientes();

	/* Se recibe un puntero a un pendiente si es que existe */
	p = thash_remove( poratender, &size, key);

	/*Si lo hay se checa si el pendiente es GRAB o READ*/
	if(p)
		switch(p->op){
			/* Si el pendiente es GRAB se invoca a la función GRAB*/
			case GRAB :
				printf("SERVER: resolviendo GRAB de %d\n", p->cliente);
				sdbespacio_atiendeSacar( key, p->cliente );
				break;
			/* Si el pendiente es READ se invoca a la función READ*/
			case READ :
				printf("SERVER: resolviendo READ de %d\n", p->cliente);
				sdbespacio_atiendeLeer( key, p->cliente );
				break;
		}
	else
		printf("SERVER: no hubo pendientes\n");

	return 0;
}

/* int sdbespacio_atiendeSacar( char *key, unsigned int src )
 *
 * Rutina para atender la petición Sacar de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeSacar( char *key, unsigned int src ) {

	thash *tabla, *poratender;
	pendiente *p;
	unsigned int size;
	void *data;

	tabla = sdbespacio_gethash();
	data = thash_remove( tabla, &size, key );

	if( size ) {
		MPI_Send( data, size, MPI_CHAR, src, DATA, MPI_COMM_WORLD );
		printf("SERVER: Envie tupla con clave %s a %d\n", key, src);
		free(data);
	} else {
		poratender = sdbespacio_getpendientes();
		NEWPENDIENTE(p);
		p->key = strdup(key);
		p->cliente = src;
		p->op = GRAB;
		thash_insert(poratender, p, sizeof(pendiente), key );
		printf("SERVER: clave no encontrada, anexando peticion GRAB a pendientes\n");
	}

	return 0;
}

/* int sdbespacio_atiendeLeer( char *key, unsigned int src )
 *
 * Rutina para atender la petición Leer de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeLeer( char *key, unsigned int src ) {

	thash *tabla, *poratender;
	pendiente *p;
	unsigned int size;
	void *data;

	tabla = sdbespacio_gethash();
	data = thash_read( tabla, &size, key );

	if( size ) {
		MPI_Send( data, size, MPI_CHAR, src, DATA, MPI_COMM_WORLD );
		printf("SERVER: Envie tupla con clave %s de %d bytes\n", key, size);
		free(data);
	} else {
		poratender = sdbespacio_getpendientes();
		NEWPENDIENTE(p);
		p->key = strdup(key);
		p->cliente = src;
		p->op = READ;
		thash_insert(poratender, p, sizeof(pendiente), key );
		printf("SERVER: clave no encontrada, anexando peticion READ a pendientes\n");
	}

	return 0;
}

/* int sdbespacio_atiendeSuprimir( char *key )
 *
 * Rutina para atender la petición Suprimir.
 */

int sdbespacio_atiendeSuprimir( char *key ) {

	thash *tabla = sdbespacio_gethash();
	unsigned int size;
	void *data;

	data = thash_remove( tabla, &size, key );

	if( size ){
		free(data);
		printf("SERVER: Operacion de borrado realizada\n");
	}
	else
		printf("SERVER: Operacion de borrado fallida, no se encontro la tupla\n");

	return 0;
}

