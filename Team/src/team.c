
#include "team.h"

int main(void)
{
	t_config_team* config = leer_config();

	t_log* logger = iniciar_logger();

	int conexion = crear_conexion(config -> ipBroker, config -> puertoBroker);

	enviar_mensaje("Hola",conexion);

	log_info(logger,"El ip es : %s", config -> ipBroker);
	log_info(logger,"El port es : %s ", config -> puertoBroker);
	terminar_programa(conexion, logger, config);
}


t_log* iniciar_logger(void)
{
	if (log_create("team.log", "team", 1, LOG_LEVEL_INFO) == NULL){
		printf("ERROR EN LA CREACION DEL LOGGER/n");
		exit(1);
				}

	return log_create("team.log", "team", 1, LOG_LEVEL_INFO);

}

t_config_team* leer_config() {
	t_config* config;

	t_config_team* config_team = malloc(sizeof(t_config_team));

	 config = config_create("Debug/broker.config");

	 config_team -> tiempoReintentoConexion = config_get_int_value(config, "TIEMPO_DE_REINTENTO_CONEXION");
	 config_team -> tiempoReintentoOperacion = config_get_int_value(config, "TIEMPO_DE_REINTENTO_OPERACION");
	 config_team -> puntoMontajeTallgras = strdup(config_get_string_value(config, "PUNTO_MONTAJE_TALLGRASS"));
	 config_team -> ipBroker = strdup(config_get_string_value(config, "IP_BROKER"));
	 config_team -> puertoBroker = strdup(config_get_string_value(config, "PUERTO_BROKER"));

	 config_destroy(config);

	 return config_team;
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_logger(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
