#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<signal.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include<pthread.h>


typedef struct {
    int tiempo_reintento_conexion;
	int tiempo_reintento_operacion;
	char* punto_montaje_tallgrass;
	char* ip_broker;
	char* puerto_broker;
} t_config_gameCard;

typedef enum {
	MENSAJE = 1,
}op_code;

typedef struct {
	int size;
	void* stream;
} t_buffer;

typedef struct {
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

pthread_t thread;
t_log* logger;


//client
void* serializar_paquete(t_paquete* paquete, int* bytes);
int crear_conexion(char* ip, char* puerto);
void enviar_mensaje(char* mensaje, int socket_cliente);

//server
void eliminar_paquete(t_paquete* paquete);
void* recibir_mensaje(int socket_cliente, int* size);
void iniciar_servidor(char *IP, char *PUERTO);
void esperar_cliente(int);
void serve_client(int *socket);
void process_request(int cod_op, int cliente_fd);
void devolver_mensaje(void* payload, int size, int socket_cliente);
int recibir_operacion(int);


void liberar_conexion(int socket_cliente);
void liberar_logger(t_log* logger);


#endif /* UTILS_H_ */
