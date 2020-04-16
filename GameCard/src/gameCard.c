#include "gameCard.h"

int main(void) {
	t_config_gameCard* config = leer_config();
	logger = iniciar_logger();

	int socket = crear_conexion(config -> ip_broker, config -> puerto_broker);


	enviar_mensaje("Get Pokemon", socket);

	//t_buffer* recibido = recibir_mensaje(socket, strlen("Hola")+ 1);


	log_info(logger, "El ip es : %s", config -> ip_broker);
	log_info(logger, "El port es : %s ", config -> puerto_broker);
	terminar_programa(socket, logger, config);
}


t_log* iniciar_logger(void) {

	t_log* logger = log_create("gameCard.log", "gameCard", 1, LOG_LEVEL_INFO);

	if (logger == NULL){
		printf("ERROR EN LA CREACION DEL LOGGER/n");
		exit(1);
	}
	return logger;
}

t_config_gameCard* leer_config() {

	t_config_gameCard* config_gameCard = malloc(sizeof(t_config_gameCard));

	t_config* config = config_create("Debug/gameCard.config");

	config_gameCard -> tiempo_reintento_conexion = config_get_int_value(config, "TIEMPO_DE_REINTENTO_CONEXION");
	config_gameCard -> tiempo_reintento_operacion = config_get_int_value(config, "TIEMPO_DE_REINTENTO_OPERACION");
	config_gameCard -> punto_montaje_tallgrass = strdup(config_get_string_value(config, "PUNTO_MONTAJE_TALLGRASS"));
	config_gameCard -> ip_broker = strdup(config_get_string_value(config, "IP_BROKER"));
	config_gameCard -> puerto_broker = strdup(config_get_string_value(config, "PUERTO_BROKER"));

	config_destroy(config);

	return config_gameCard;
}

void terminar_programa(int conexion,t_log* logger,t_config_gameCard* config) {
	liberar_config(config);
	liberar_logger(logger);
	liberar_conexion(conexion);
}
