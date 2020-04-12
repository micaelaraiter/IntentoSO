#include "broker.h"

int main(void) {
	    /* int socket_de_conexion;
	    int sizeMemoria;
	    int sizeMinMemoria;

	    t_log* logger;
		t_config* config;

	    char* algoritmoMemoria = string_new();
	    char* algoritmoReemplazo= string_new();
	    char* algoritmoParticionLibre= string_new();
		char* ip = string_new();
		char* puerto= string_new();

	 	 cambio la forma de asignarle el valor a nuestras variables, los que obtiene del config

		string_append(&algoritmoMemoria,config_get_string_value(config, "ALGORITMO_MEMORIA"));
		string_append(&algoritmoReemplazo,config_get_string_value(config, "ALGORITMO_REEMPLAZO"));
		string_append(&algoritmoParticionLibre, config_get_string_value(config, "ALGORITMO_PARTICION_LIBRE"));
		string_append(&ip,config_get_string_value(config, "IP_BROKER"));
		string_append(&puerto, config_get_string_value(config, "PUERTO_BROKER")); */

		t_log* logger;
		t_config* config;
		t_config_broker datos_de_config = leer_config();

		logger = iniciar_logger();

	    socket_de_conexion = crear_conexion(ip, puerto);

		terminar_programa(socket_de_conexion, logger, config);
}



//TODO
t_log* iniciar_logger(void) {
	return log_create("broker.log","broker",1,LOG_LEVEL_INFO);
}

//TODO

t_config_broker leer_config(void)
{
	t_config* config;
    t_config_broker configBroker;

	 config = config_create("Debug/broker.config");

	 configBroker.sizeMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
	 configBroker.sizeMinMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
	 string_append(&configBroker.algoritmoMemoria ,config_get_string_value(config, "ALGORITMO_MEMORIA"));
	 string_append(&configBroker.algoritmoReemplazo,config_get_string_value(config, "ALGORITMO_REEMPLAZO"));
	 string_append(&configBroker.algoritmoParticionLibre, config_get_string_value(config, "ALGORITMO_PARTICION_LIBRE"));
	 string_append(&configBroker.ip,config_get_string_value(config, "IP_BROKER"));
	 string_append(&configBroker.puerto, config_get_string_value(config, "PUERTO_BROKER"));
	 configBroker.frecuenciaCompactacion = config_get_int_value(config, "FRECUENCIA_COMPACTACION");

	 return configBroker;
}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config) {
	close(conexion);
	log_destroy(logger);
	config_destroy(config);
}
