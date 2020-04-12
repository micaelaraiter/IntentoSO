typedef struct
{
	int conexion;
    int sizeMemoria;
	int sizeMinMemoria;
	char* algoritmoMemoria;
	char* algoritmoReemplazo;
	char* algoritmoParticionLibre;
	char* ip;
	char* puerto;
	int frecuenciaCompactacion;
} config_broker;


#include "broker.h"

int main(void)
{
	    int conexion;
	    int sizeMemoria;
	    int sizeMinMemoria;
	    char* algoritmoMemoria = string_new();
	    char* algoritmoReemplazo= string_new();
	    char* algoritmoParticionLibre= string_new();
		char* ip = string_new();
		char* puerto= string_new();
		int frecuenciaCompactacion;

		t_log* logger;
		t_config* config;

		logger = iniciar_logger();
		leer_config();

		sizeMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
		sizeMinMemoria = config_get_int_value(config, "TAMANO_MEMORIA");
		string_append(&algoritmoMemoria,config_get_string_value(config, "ALGORITMO_MEMORIA"));
		string_append(&algoritmoReemplazo,config_get_string_value(config, "ALGORITMO_REEMPLAZO"));
		string_append(&algoritmoParticionLibre, config_get_string_value(config, "ALGORITMO_PARTICION_LIBRE"));
		string_append(&ip,config_get_string_value(config, "IP_BROKER"));
		string_append(&puerto, config_get_string_value(config, "PUERTO_BROKER"));
		frecuenciaCompactacion = config_get_int_value(config, "FRECUENCIA_COMPACTACION");
	    //conexion = crear_conexion(ip, puerto);

		terminar_programa(conexion, logger, config);
}



//TODO
t_log* iniciar_logger(void)
{
	return log_create("log.txt","tp0.h",1,LOG_LEVEL_INFO);
}

//TODO
config_broker leer_config(void)
{
	t_config* config;
     config_broker configBroker;
	 config_create("Debug/broker.config");
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
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	//liberar_conexion(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
