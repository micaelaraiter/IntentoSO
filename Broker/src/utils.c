#include "utils.h"

extern int pthread_create (pthread_t *__restrict __newthread,
			   	   	   	   const pthread_attr_t *__restrict __attr,
						   void *(*__start_routine) (void *),
						   void *__restrict __arg) __THROWNL __nonnull ((1, 3));
extern int pthread_detach (pthread_t __th) __THROW;

/*
 * Recibe un paquete a serializar, y un puntero a un int en el que dejar
 * el tamaño del stream de bytes serializados que devuelve
 */
void* serializar_paquete(t_paquete* paquete, int* bytes) {
	int malloc_size = paquete -> buffer -> size + sizeof(op_code) + sizeof(int);
	void* _stream = malloc(malloc_size);
	int offset = 0;

	memcpy(_stream+offset, &(paquete -> codigo_operacion), sizeof(paquete -> codigo_operacion));
	offset += sizeof(paquete -> codigo_operacion);
	memcpy(_stream + offset, &(paquete -> buffer -> size), sizeof(paquete -> buffer -> size));
	offset += sizeof(paquete -> buffer -> size);
	memcpy(_stream + offset, paquete -> buffer -> stream, paquete -> buffer -> size);
	offset += paquete -> buffer -> size;

	(*bytes) = malloc_size;
	log_info(logger, "%d", bytes);
	return _stream;
}

void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_buffer* buffer = malloc(sizeof(t_buffer));

	buffer -> size = strlen(mensaje) + 1;
	buffer -> stream = malloc(buffer -> size);
	memcpy(buffer -> stream,mensaje,buffer -> size);

	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete -> codigo_operacion = MENSAJE;
	paquete -> buffer = buffer;

	int size_serializado;
	void* stream = serializar_paquete(paquete, &size_serializado);

	// int header = sizeof(paquete -> codigo_operacion) + paquete -> buffer -> size + sizeof(paquete -> buffer -> size);
	send(socket_cliente, stream, size_serializado, 0);

	free(buffer -> stream);
	free(buffer);
	free(paquete);
	free(stream);
}

void* recibir_mensaje(int socket_cliente, int* size) {
	t_paquete* paquete = malloc(sizeof(t_paquete));
	void* buffer = malloc(sizeof(t_buffer));

	log_info(logger,"Recibiendo mensaje.");
	recv(socket_cliente, buffer, *size, MSG_WAITALL);
	log_info(logger,"Tamaño de paquete recibido: %d",*size);

	buffer = malloc(*size);

	recv(socket_cliente, buffer, *size, MSG_WAITALL);
	log_info(logger,"Mensaje recibido.");
	return buffer;
}

void iniciar_servidor(char *IP, char *PUERTO) {
	int socket_servidor;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(IP, PUERTO, &hints, &servinfo);

    for (p=servinfo; p != NULL; p = p -> ai_next) {
        if ((socket_servidor = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) == -1)
            continue;

        if (bind(socket_servidor, p -> ai_addr, p -> ai_addrlen) == -1) {
            close(socket_servidor);
            continue;
        }
        break;
    }

	listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);
    log_info(logger,"Servidor levantdo.");
    while(1)
    	esperar_cliente(socket_servidor);
}

void esperar_cliente(int socket_servidor) {
	struct sockaddr_in dir_cliente;

	int tam_direccion = sizeof(struct sockaddr_in);

	int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);
	pthread_create(&thread,NULL,(void*)serve_client,&socket_cliente);
	pthread_detach(thread);

}

void serve_client(int* socket) {
	int cod_op;
	if(recv(*socket, &cod_op, sizeof(int), MSG_WAITALL) == -1)
		cod_op = -1;
	log_info(logger,"Se conecto un cliente con socket: %d",*socket);
	process_request(cod_op, *socket);
	printf("el valor de socket es : %d", (int)* (socket));
}

void process_request(int cod_op, int cliente_fd) {
	int size;
	void* msg;
	log_info(logger,"Codigo de operacion %d",cod_op);
	switch (cod_op) {
		case MENSAJE:
			msg = recibir_mensaje(cliente_fd, &size);
			devolver_mensaje(msg, size, cliente_fd);
			free(msg);
			break;
		case 0:
			pthread_exit(NULL);
		case -1:
			pthread_exit(NULL);
	}
}

void devolver_mensaje(void* payload, int size, int socket_cliente) {
	log_info(logger,"Devolviendo mensaje");

	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = size;
	paquete->buffer->stream = malloc(paquete -> buffer -> size);
	memcpy(paquete -> buffer -> stream, payload, paquete -> buffer -> size);

	int bytes = paquete -> buffer -> size + 2 * sizeof(int);
	void* a_enviar = serializar_paquete(paquete, &bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	free(paquete -> buffer -> stream);
	free(paquete -> buffer);
	free(paquete);
	log_info(logger,"Mensaje devuelto");
}


void liberar_conexion(int socket_cliente) {
	close(socket_cliente);
}

void liberar_logger(t_log* logger){
	if(logger != NULL){
		log_destroy(logger);
	}
}
