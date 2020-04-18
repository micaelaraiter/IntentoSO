#include "team.h"

int main(void) {

	t_config_team* config = leer_config();
	logger = iniciar_logger();

	int socket = crear_conexion(config -> ip_broker, config -> puerto_broker);


	enviar_mensaje("Get Pokemon", socket);

	//t_buffer* recibido = recibir_mensaje(socket, strlen("Hola")+ 1);
	int size;
	void* mensaje= malloc(12);
    mensaje = recibir_mensaje(socket,&size);
    free(mensaje);
	log_info(logger, "El ip es : %s", config -> ip_broker);
	log_info(logger, "El port es : %s ", config -> puerto_broker);
	terminar_programa(socket, logger, config);
}


t_log* iniciar_logger(void) {

	t_log* logger = log_create("team.log", "team", 1, LOG_LEVEL_INFO);

	if (logger == NULL){
		printf("ERROR EN LA CREACION DEL LOGGER/n");
		exit(1);
	}
	return logger;
}

t_config_team* leer_config() {

	t_config_team* config_team = malloc(sizeof(t_config_team));

	t_config* config = config_create("Debug/team.config");

	config_team -> tiempo_reintento_conexion = config_get_int_value(config, "TIEMPO_DE_REINTENTO_CONEXION");
	config_team -> tiempo_reintento_operacion = config_get_int_value(config, "TIEMPO_DE_REINTENTO_OPERACION");
	config_team -> punto_montaje_tallgrass = strdup(config_get_string_value(config, "PUNTO_MONTAJE_TALLGRASS"));
	config_team -> ip_broker = strdup(config_get_string_value(config, "IP_BROKER"));
	config_team -> puerto_broker = strdup(config_get_string_value(config, "PUERTO_BROKER"));

	config_destroy(config);

	return config_team;
}

void terminar_programa(int conexion,t_log* logger,t_config_team* config) {
	liberar_config(config);
	liberar_logger(logger);
	liberar_conexion(conexion);
}
