/*
 * main.c
 */

#include "Team.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	config = leer_config();
	memcpy(config_get_string_value(config, "IP_BROKER"), ip, sizeof(config_get_string_value(config, "IP_BROKER")));
	log_info(logger,ip);
	puerto = config_get_string_value(config, "PORT_BROKER");
	log_info(logger,puerto);
    int socket = crear_conexion(ip, puerto);
	terminar_programa(conexion, logger, config);
}

//TODO
t_log* iniciar_logger(void)
{
	return log_create("log.txt","tp0.h",1,LOG_LEVEL_INFO);
}

//TODO
t_config* leer_config()
{
	return config_create("team.config");
}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
