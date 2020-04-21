#include "gameBoy.h"

int main(void) {
	t_config_game_boy* config = leer_config();
	logger = iniciar_logger();

	//int socket = crear_conexion(config -> ip_broker, config -> puerto_broker)
	//enviar_mensaje(GC_LOCALIZED_POKEMON_BR, "Localized Pokemon", socket);

	//t_buffer* recibido = recibir_mensaje(socket, strlen("Hola")+ 1);
	char opcion[3];
	printf("Seleccione el mensaje que desea enviar\n 1-GET_POKEMON \n 2.CATCH_POKEMON \n 3.LOCALIZED_POKEMON \n 4.CAUGHT_POKEMON \n 5.APPEARED_POKEMON \n 6.NEW_POKEMON ");
	fgets(opcion,3,stdin);

	log_info(logger, "El codigo seleccionado es : %s", opcion);


	log_info(logger, "El ip es : %s", config -> ip_broker);
	log_info(logger, "El port es : %s ", config -> puerto_broker);
	terminar_programa(socket, logger, config);
}


t_log* iniciar_logger(void) {

	t_log* logger = log_create("gameBoy.log", "gameBoy", 1, LOG_LEVEL_INFO);

	if (logger == NULL){
		printf("ERROR EN LA CREACION DEL LOGGER/n");
		exit(1);
	}
	return logger;
}

t_config_game_boy* leer_config() {

	t_config_game_boy* config_game_boy = malloc(sizeof(t_config_game_boy));

	t_config* config = config_create("Debug/gameBoy.config");

	config_game_boy -> ip_broker = strdup(config_get_string_value(config, "IP_BROKER"));
	config_game_boy-> puerto_broker = strdup(config_get_string_value(config, "PUERTO_BROKER"));
	config_game_boy -> ip_team = strdup(config_get_string_value(config, "IP_TEAM"));
	config_game_boy-> puerto_team = strdup(config_get_string_value(config, "PUERTO_TEAM"));
	config_game_boy -> ip_gameCard = strdup(config_get_string_value(config, "IP_GAMECARD"));
	config_game_boy-> puerto_gameCard = strdup(config_get_string_value(config, "PUERTO_GAMECARD"));

	config_destroy(config);

	return config_game_boy;
}




void liberar_config(t_config_game_boy* config) {

	free(config);
}

void terminar_programa(int conexion,t_log* logger, t_config_game_boy* config) {
	liberar_config(config);
	liberar_logger(logger);
	liberar_conexion(conexion);
}
