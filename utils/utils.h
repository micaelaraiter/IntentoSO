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
    int size_memoria;
	int size_min_memoria;
	char* algoritmo_memoria;
	char* algoritmo_reemplazo;
	char* algoritmo_particion_libre;
	char* ip_broker;
	char* puerto;
	int frecuencia_compactacion;
} t_config_broker;

typedef enum {
	MENSAJE = 1,
	//Team a Broker
	TE_GET_POKEMON_BR = 1,
	TE_CATCH_POKEMON_BR = 2,
	//Gamecard a Broker
	GC_LOCALIZED_POKEMON_BR = 3,
	GC_CAUGHT_POKEMON_BR = 4,
	//Gameboy a Team
	GB_APPEARED_POKEMON_TE = 5,
	//Gameboy a Gamecard
	GB_NEW_POKEMON_GC = 6,
	GB_GET_POKEMON_GC = 7,
	GB_CATCH_POKEMON_GC = 8,
	//Gameboy a Broker
	GB_NEW_POKEMON_BR = 9,
	GB_CAUGHT_POKEMON_BR = 10,
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

void* serializar_paquete(t_paquete* paquete, int* bytes);
void enviar_mensaje(char* mensaje, int socket_cliente);

void eliminar_paquete(t_paquete* paquete);
void* recibir_mensaje(int socket_cliente, int* size);
void* recibir_buffer(int*, int); /// este no esta definido en utils.c

void iniciar_servidor(char *IP, char *PUERTO);
void esperar_cliente(int);
void serve_client(int *socket);
int recibir_operacion(int);
void process_request(int cod_op, int cliente_fd);

void devolver_mensaje(void* payload, int size, int socket_cliente);

void liberar_config(t_config_broker*);
void liberar_conexion(int socket_cliente);
void liberar_logger(t_log* logger);

#endif /* UTILS_H_ */
