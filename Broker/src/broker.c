#include "broker.h"
#include "utils.h"

int main(void) {

	    int socket_team;
	    int socket_gamecard;

		t_log* logger = iniciar_logger();

		// log_info(logger, "leer la config");
		t_config_broker* datos_de_config = leer_config(logger);
		// log_info(logger, "leer la config");

		// log_info(logger, "socket team");
	    socket_team = crear_conexion(datos_de_config -> ip_team, datos_de_config -> puerto_team);

	    // log_info(logger, "socket gamecard");
	    socket_gamecard = crear_conexion(datos_de_config -> ip_gamecard, datos_de_config -> puerto_gamecard);

	    char* mensaje = mensaje;


	    // log_info(logger, "terminar programa");
		terminar_programa(socket_team, socket_gamecard, logger, datos_de_config);
		// log_info(logger, "programa terminado");

}


t_log* iniciar_logger(void) {

	t_log* un_logger;

	if((un_logger = log_create("broker.log", "broker", 1, LOG_LEVEL_INFO)) == NULL){
		printf("fallo la creacion del logger\n");
		exit(1);
	}
	return un_logger;
}

t_config_broker* leer_config(t_log* logger) {
	t_config* config;

	log_info(logger, "peso malloc config %d", sizeof(t_config_broker));

	t_config_broker* config_broker = malloc(sizeof(t_config_broker)+13);

	 config = config_create("Debug/broker.config");

	 config_broker -> sizeMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
	 config_broker -> sizeMinMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
	 config_broker -> algoritmoMemoria = config_get_string_value(config, "ALGORITMO_MEMORIA");
	 config_broker -> algoritmoReemplazo = config_get_string_value(config, "ALGORITMO_REEMPLAZO");
	 config_broker -> algoritmoParticionLibre = config_get_string_value(config, "ALGORITMO_PARTICION_LIBRE");
	 config_broker -> ip_team = config_get_string_value(config, "IP_BROKER_TEAM");
	 config_broker -> puerto_team = config_get_string_value(config, "PUERTO_BROKER_TEAM");
	 config_broker -> ip_gamecard = config_get_string_value(config, "IP_BROKER_GAMECARD");
	 config_broker -> puerto_gamecard = config_get_string_value(config, "PUERTO_BROKER_GAMECARD");
	 config_broker -> frecuenciaCompactacion = config_get_int_value(config, "FRECUENCIA_COMPACTACION");

	 config_destroy(config);

	 return config_broker;
}

void terminar_programa(int socket_team, int socket_gamecard, t_log* logger, t_config_broker* datos_de_config) {

	free(datos_de_config);
	liberar_conexion(socket_gamecard);
	liberar_conexion(socket_team);
	liberar_logger(logger);
}
