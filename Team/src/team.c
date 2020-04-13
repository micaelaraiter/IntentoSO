/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "team.h"

int main(void)
{
	    int conexion;
		char* ip;
		char* puerto;

		t_log* logger;
		t_config* config;

		logger = iniciar_logger();
		config = leer_config();
		ip = config_get_string_value(config,"IP");
		puerto = config_get_string_value(config,"PUERTO");

	    conexion = crear_conexion(ip,puerto);
		enviar_mensaje("hola",conexion);
		liberar_conexion(conexion);
//
//		printf("El ip es : %s",ip);
//		printf("El port es : %s ",puerto);
		recibir_mensaje_cliente(conexion);
		terminar_programa(conexion, logger, config);
}


t_log* iniciar_logger(void)
{
	if (log_create("team.log", "team", 1, LOG_LEVEL_INFO) == NULL){
		printf("ERROR EN LA CREACION DEL LOGGER/n");
		exit(1);
				}

	return log_create("team.log", "team", 1, LOG_LEVEL_INFO);

}


t_config* leer_config(void)
{
	if (config_create("Debug/team.config") == NULL){
		printf("ERROR EN LA CONFIG/n");
		exit(2);
	}
	return config_create("Debug/team.config");
}


void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	//liberar_conexion(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
