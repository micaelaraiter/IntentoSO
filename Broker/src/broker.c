#include "broker.h"
#include "utils.h"

int main(void) {

		t_log* logger = iniciar_logger();

		t_config_broker* datos_de_config = leer_config(logger);
		// log_info(logger, "config leida");



	    // log_info(logger, "terminar programa");
		terminar_programa(logger, datos_de_config);
		// log_info(logger, "programa terminado");

}


t_log* iniciar_logger(void) {

	t_log* logger;

	if((logger = log_create("broker.log", "broker", 1, LOG_LEVEL_INFO)) == NULL){
		printf("fallo la creacion del logger\n");
		exit(1);
	}
	return logger;
}

t_config_broker* leer_config() {
	t_config* config;

	t_config_broker* config_broker = malloc(sizeof(t_config_broker));

	 config = config_create("Debug/broker.config");

	 config_broker -> sizeMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
	 config_broker -> sizeMinMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
	 config_broker -> algoritmoMemoria = strdup(config_get_string_value(config, "ALGORITMO_MEMORIA"));
	 config_broker -> algoritmoReemplazo = strdup(config_get_string_value(config, "ALGORITMO_REEMPLAZO"));
	 config_broker -> algoritmoParticionLibre = strdup(config_get_string_value(config, "ALGORITMO_PARTICION_LIBRE"));
	 config_broker -> ip_team = strdup(config_get_string_value(config, "IP_BROKER_TEAM"));
	 config_broker -> puerto_team = strdup(config_get_string_value(config, "PUERTO_BROKER_TEAM"));
	 config_broker -> ip_gamecard = strdup(config_get_string_value(config, "IP_BROKER_GAMECARD"));
	 config_broker -> puerto_gamecard = strdup(config_get_string_value(config, "PUERTO_BROKER_GAMECARD"));
	 config_broker -> frecuenciaCompactacion = config_get_int_value(config, "FRECUENCIA_COMPACTACION");

	 config_destroy(config);

	 return config_broker;
}

void terminar_programa(t_log* logger, t_config_broker* datos_de_config) {

	free(datos_de_config);
	liberar_logger(logger);
}
