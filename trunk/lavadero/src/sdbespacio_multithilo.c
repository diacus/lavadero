/*
 * sdbmaestro.c
 *
 *  Created on: 16/05/2010
 *      Author: diacus
 */

#include <sdbespacio.h>

#ifdef MULTITHREAD

/* thash *sdbespacio_gethash()
 *
 * Función para obtener una referencia a la tabla hash en la
 * que almacenan las tuplas.
 */

thash *sdbespacio_gethash() {

	static int    creadaHash = 0;
	static thash *tabla      = NULL;

	if( ! creadaHash ) {
		creadaHash ++;                	/* Esta parte puede ser parametrizada con */
		tabla = thash_new(TABLESIZE);	/* un archivo de configuración            */
	}

	return tabla;
}


/* thash *sdbespacio_getpendientes()
 *
 * Funcipon para obtener una referencia al espacio en el que
 * se van a almacenar las peticiones pendientes.
 */

thash *sdbespacio_getpendientes() {

	static int    creadaPendientes = 0;
	static thash *pendientes       = NULL;


	if( ! creadaPendientes ) {
		creadaPendientes ++;               	/* Esta parte puede ser parametrizada con */
		pendientes = thash_new(TABLESIZE);	/* un archivo de configuración            */
	}

	return pendientes;
}


/* datos *sdbespacio_getdatos()
 *
 * Obtiene un apuntador a los datos compartidos por los
 * hilos del espacio de tuplas.
 */

datos *sdbespacio_getdatos() {
	static datos *res          = NULL;
	static int    creadosDatos = 0;

	if( !creadosDatos ) {
		estado *edo = sdbproceso_estado();
		res = (datos *) malloc( sizeof(datos) );
		res->cliente = (char *) calloc( edo->num_procs - MAESTRO - 1, sizeof(char) );
	}

	return res;
}


/* datos *sdbespacio_deletedatos( datos *d )
 *
 */

datos *sdbespacio_deletedatos( datos *d ) {
	if ( d ) {
		free( d->cliente );
		free( d );
	}
	return 0;
}

/* int sdbmaestro_iniciar()
 *
 * Función para inicializar el especio de tuplas.
 */

int sdbespacio_iniciar() {
	int     i, salida, error = 0;
	hilo    hilos[NHILOS];                /* El espacio de tuplas es multi-hilado. */
	datos  *args = sdbespacio_getdatos();

	for( i = 0; i < NHILOS; i++ ) { /* Lanzando los hilos para atender peticiones */
		error = pthread_create( hilos + i, NULL ,sdbespacio_atender, (void *) i );
		if( error )
			fprintf( stderr, "Error %d: %s\n", error, strerror(error) );
	}

	for( i = 0; i < NHILOS; i++ ) { /* Esperando que terminen los hilos */
		error = pthread_join( hilos[i], (void **) &salida );
		if( error )
			fprintf( stderr, "Error %d: %s\n", error, strerror(error) );
	}

	args = sdbespacio_deletedatos(args);
	return 0;
}

int sdbespacio_disponible( int id ) {

	datos *args = sdbespacio_getdatos();
	int    res;

	if (args->cliente[id - MAESTRO - 1] == 0 ) {
		args->cliente[id - MAESTRO - 1] = '1';
		res = 1;
	} else
		res = 0;

	return res;
}

/* void *sdbespacio_atender( void *args )
 *
 */

void *sdbespacio_atender( void *param ) {

	thash  *tabla  = sdbespacio_gethash();  /* Apuntador a tabla hash.               */
	estado *edo    = sdbproceso_estado();   /* Apuntador a estado (propio de LINDA). */
	datos  *args   = sdbespacio_getdatos(); /* Variables compartidas por los hilos.  */
	char   *buffer;                         /* Buffer de mensaje a recibir.          */
	int     nbytes,                         /* Tamaño (nbytes) del buffer a recibir, */
            source,                         /* identidad (source) del emisor y       */
            tag,                            /* etiqueta (tag) del mensaje.           */
            entrante,                       /* Bandera que indica si hay mensajes.   */
            disponible;

	printf( "Hilo[%2d]: Lanzado por el proceso %d para atender el espacio de tuplas\n",
			(int) param, edo->my_rank);

	while( edo->tag != END ) {
		MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &entrante, &(edo->status));

		if( entrante ) {
			pthread_mutex_lock( &args->lock_procesos );
			source     = (edo->status).MPI_SOURCE;
			disponible = sdbespacio_disponible( source );
			pthread_mutex_lock( &args->lock_procesos );

			if( disponible ) {
				printf( "Hilo[%2d]: En el proceso %d para atender al cliente %d\n",
						(int) param, edo->my_rank, source );
				MPI_Get_count(&(edo->status), MPI_BYTE, &nbytes);
				buffer = (char *) calloc( nbytes, sizeof(char) );
				tag    = (edo->status).MPI_TAG;
				MPI_Recv( buffer, nbytes, MPI_BYTE, source, tag, MPI_COMM_WORLD, &(edo->status) );

				switch(tag) {
				case END :
					edo->tag = END;
					break;
				case STORE :
					sdbespacio_atiendeMeter( buffer, nbytes, tabla );
					break;
				case GRAB :
					sdbespacio_atiendeSacar( buffer, source, tabla );
					break;
				case READ :
					sdbespacio_atiendeLeer( buffer, source, tabla );
					break;
				case DROP :
					sdbespacio_atiendeSuprimir ( buffer, tabla );
					break;
				default:
					fprintf( stderr, "Error: Tarea no soportada por el programa.\n" );
				}
				DELETE_MESSAGE(buffer);
				LIBERA_PROCESO(source, args);
			}
		}
	}

	pthread_exit(param);
}

/* unsigned int sdbespacio_atiendeMeter( char * message, int sz )
 *
 * Función que recibe un mensaje y el tamaño en bytes de éste
 * almacena en la tabla hash la tupla contenida en el mensaje
 * empleando la clave también empaquetada en el mensaje
 *
 */

unsigned int sdbespacio_atiendeMeter( char *message, int sz, thash *tabla ){

	thash     *poratender;  /* Creación de apuntador a la tabla hash de indices y tabla de pendientes   */
	pendiente *p;           /* apuntador a la estructura pendiente                                      */
	tupla      data;        /* Tupla a almacenar                                                        */
	char      *key;         /* Clave de la tupla                                                        */
	int        indice, tam; /* índice de la tabla en el que se almacenará la tupla y tamaño de la tupla */
	int        error = 0;
	datos     *args;        /* Contiene los datos compartidos por los hilos, */
                            /* incluyendo candados para el espacio de tuplas */
                            /* y las solicitudes pendientes.                 */

	args       = sdbespacio_getdatos();
	poratender = sdbespacio_getpendientes();
	tam        = sdbproceso_unpack( message, sz, &key, &data);

	pthread_mutex_lock( &args->lock_tabla );
	indice = thash_insert(tabla, data, key );
	pthread_mutex_unlock( &args->lock_tabla );

	pthread_mutex_lock( &args->lock_pendientes );
	p = thash_remove( poratender, key );
	pthread_mutex_unlock( &args->lock_pendientes );

	if( p ) {
		switch( p->op ) {
			case GRAB :
				sdbespacio_atiendeSacar( key, p->cliente, tabla );
				break;
			case READ :
				sdbespacio_atiendeLeer( key, p->cliente, tabla );
				break;
		}
		DELETEPENDIENTE(p);
		error++;
	}
	return error;
}

/* int sdbespacio_atiendeSacar( char *key, unsigned int src )
 *
 * Rutina para atender la petición Sacar de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeSacar( char *key, unsigned int src, thash *tabla ) {

	int        error = 0;
	thash     *poratender;
	pendiente *p;
	tupla     *data;
	datos     *args;

	args       = sdbespacio_getdatos();

	pthread_mutex_lock( &args->lock_tabla );
	data = thash_remove( tabla, key );
	pthread_mutex_unlock( &args->lock_tabla );

	if( data ) {
		MPI_Send( data, TUPLA_SIZE(data), MPI_CHAR, src, DATA, MPI_COMM_WORLD );
		DELETE_MESSAGE(data);
	} else {
		poratender = sdbespacio_getpendientes();
		NEWPENDIENTE(p);
		p->key = strdup(key);
		p->cliente = src;
		p->op = GRAB;

		pthread_mutex_lock( &args->lock_pendientes );
		thash_insert(poratender, p, key );
		pthread_mutex_unlock( &args->lock_pendientes );
		error++;
	}

	return error;
}

/* int sdbespacio_atiendeLeer( char *key, unsigned int src )
 *
 * Rutina para atender la petición Leer de un cliente, y
 * proporcionarle la tupla que solicitó.
 */

int sdbespacio_atiendeLeer( char *key, unsigned int src, thash *tabla ) {

	int        error = 0;
	thash     *poratender;
	pendiente *p;
	tupla      data;
	datos     *args;

	args = sdbespacio_getdatos();

	pthread_mutex_lock( &args->lock_tabla );
	data = thash_read( tabla, key );
	pthread_mutex_unlock( &args->lock_tabla );

	if( data )
		MPI_Send( data, TUPLA_SIZE(data), MPI_CHAR, src, DATA, MPI_COMM_WORLD );
	else {
		poratender = sdbespacio_getpendientes();
		NEWPENDIENTE(p);
		p->key     = strdup(key);
		p->cliente = src;
		p->op      = READ;
		pthread_mutex_lock( &args->lock_pendientes );
		thash_insert(poratender, p, key );
		pthread_mutex_unlock( &args->lock_pendientes );
		error++;
	}

	return error;
}

/* int sdbespacio_atiendeSuprimir( char *key )
 *
 * Rutina para atender la petición Suprimir.
 */

int sdbespacio_atiendeSuprimir( char *key, thash *tabla ) {

	int    error = 0;
	tupla *data;
	datos *args;

	args = sdbespacio_getdatos();

	pthread_mutex_lock( &args->lock_tabla );
	data = thash_remove( tabla, key );
	pthread_mutex_unlock( &args->lock_tabla );

	if( data )
		DELETE_MESSAGE(data)
	else
		error++;

	return error;
}
#endif
