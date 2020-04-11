/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "GameCard.h"

int main(void)
{
	    int conexion;
		char* ip = malloc(4);
		char* puerto= malloc(4);;

		t_log* logger;
		t_config* config;

		logger = iniciar_logger();
		config = leer_config();
		memcpy(config_get_string_value(config, "IP_BROKER"), ip, sizeof(config_get_string_value(config, "IP_BROKER")));

		puerto = config_get_string_value(config, "PORT_BROKER");

	    int socket = crear_conexion(ip, puerto);
		terminar_programa(conexion, logger, config);
}

//TODO
t_log* iniciar_logger(void)
{
	return log_create("log.txt","tp0.h",1,LOG_LEVEL_INFO);
}

//TODO
t_config* leer_config(void)
{
	return config_create("gameCard.config");
}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
