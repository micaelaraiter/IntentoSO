#include "broker.h"

int main(void) {

		logger = iniciar_logger();
		iniciar_servidor("127.0.0.1","4444");


//		t_config_broker* config = leer_config();
//		// log_info(logger, "config leida");
//
//	    // log_info(logger, "terminar programa");
//		terminar_programa(logger, config);
//		 log_info(logger, "programa terminado");

		 return EXIT_SUCCESS;
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

	 config_broker -> size_memoria = config_get_int_value(config, "TAMANO_MEMORIA");
	 config_broker -> size_min_memoria = config_get_int_value(config, "TAMANO_MEMORIA");
	 config_broker -> algoritmo_memoria = strdup(config_get_string_value(config, "ALGORITMO_MEMORIA"));
	 config_broker -> algoritmo_reemplazo = strdup(config_get_string_value(config, "ALGORITMO_REEMPLAZO"));
	 config_broker -> algoritmo_particion_libre = strdup(config_get_string_value(config, "ALGORITMO_PARTICION_LIBRE"));
	 config_broker -> ip_team = strdup(config_get_string_value(config, "IP_BROKER_TEAM"));
	 config_broker -> puerto_team = strdup(config_get_string_value(config, "PUERTO_BROKER_TEAM"));
	 config_broker -> ip_gamecard = strdup(config_get_string_value(config, "IP_BROKER_GAMECARD"));
	 config_broker -> puerto_gamecard = strdup(config_get_string_value(config, "PUERTO_BROKER_GAMECARD"));
	 config_broker -> frecuencia_compactacion = config_get_int_value(config, "FRECUENCIA_COMPACTACION");

	 config_destroy(config);

	 return config_broker;
}

void terminar_programa(t_log* logger, t_config_broker* config) {
	liberar_config(config);
	liberar_logger(logger);
}
