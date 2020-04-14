#include "broker.h"

int main(void) {

	    int socket_team;
	    int socket_gamecard;

		t_log* logger;
		logger = iniciar_logger();
		t_config_broker* datos_de_config = malloc(sizeof(t_config_broker));
		datos_de_config=leer_config();


	    iniciar_servidor("127.0.0.1", "6667");
	    //socket_gamecard = crear_conexion(datos_de_config -> ip_gamecard, datos_de_config -> puerto_gamecard);

		terminar_programa(socket_team, socket_gamecard, logger, datos_de_config);
}


t_log* iniciar_logger(void) {
	return log_create("broker.log", "broker", 1, LOG_LEVEL_INFO);
}

t_config_broker* leer_config() {

	t_config_broker* config_broker = malloc(sizeof(t_config_broker));
    t_config *config = config_create("Debug/broker.config");
    config_broker -> sizeMemoria  = config_get_int_value(config, "TAMANO_MEMORIA");
	config_broker -> sizeMinMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
	config_broker -> algoritmoMemoria = strdup(config_get_string_value(config, "ALGORITMO_MEMORIA"));
	config_broker -> algoritmoReemplazo = strdup(config_get_string_value(config, "ALGORITMO_REEMPLAZO"));
	config_broker -> algoritmoParticionLibre = strdup(config_get_string_value(config, "ALGORITMO_PARTICION_LIBRE"));
	config_broker -> ip_team = strdup(config_get_string_value(config, "IP_BROKER_TEAM"));
	config_broker -> puerto_team =strdup( config_get_string_value(config, "PUERTO_BROKER_TEAM"));
	config_broker -> ip_gamecard = strdup(config_get_string_value(config, "IP_BROKER_GAMECARD"));
	config_broker -> puerto_gamecard = strdup(config_get_string_value(config, "PUERTO_BROKER_GAMECARD"));
	//config_broker -> frecuenciaCompactacion = config_get_int_value(config, "FRECUENCIA_COMPACTACION");

	 config_destroy(config);

	 return config_broker;
}

void terminar_programa(int socket_team, int socket_gamecard, t_log* logger, t_config_broker* datos_de_config) {

	free(datos_de_config);
	close(socket_gamecard);
	close(socket_team);
	log_destroy(logger);
}
