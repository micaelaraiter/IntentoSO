#include "team.h"

int main(void) {

	leer_config();
	iniciar_logger();

	log_info(logger, "Las posiciones son:", config -> posiciones_entrenadores[0]);
	log_info(logger, "Las pokemons son:", config -> pokemon_entrenadores[0]);
	log_info(logger, "Los objetivos son:", config -> objetivos_entrenadores[0]);

	t_lista_pokemons* objetivo_global = obtener_objetivo_global();

	int socket = crear_conexion(config -> ip_broker, config -> puerto_broker);


	enviar_mensaje(TE_GET_POKEMON_BR, "Get Pokemon", socket);

	//t_buffer* recibido = recibir_mensaje(socket, strlen("Hola")+ 1);
	log_info(logger, "El ip es : %s", config -> ip_broker);
	log_info(logger, "El port es : %s ", config -> puerto_broker);
	terminar_programa(socket, logger, config);
}


void iniciar_logger(void) {

	t_log* logger = log_create(config -> log_path, "team", 1, LOG_LEVEL_INFO);

	if (logger == NULL){
		printf("ERROR EN LA CREACION DEL LOGGER/n");
		exit(1);
	}
}

t_lista_pokemons* obtener_objetivo_global(){

	t_lista_pokemons* objetivos;
	t_lista_lista_pokemons* aux_lista_lista = config -> objetivos_entrenadores;
	t_lista_pokemons* aux_lista = aux_lista_lista -> pokemons;


	while(aux_lista_lista -> next != NULL){
		while(aux_lista -> next != NULL){

			objetivos -> pokemon = aux_lista -> pokemon;
			objetivos -> next = aux_lista -> next;
			aux_lista = aux_lista -> next;
		}

		aux_lista_lista = aux_lista_lista -> next;
	}

	return objetivos;
}

void leer_config(void) {

	t_config_team* config_team = malloc(sizeof(t_config_team));

	t_config* config = config_create("Debug/team.config");

	config_team -> posiciones_entrenadores = (t_lista_posiciones*) config_get_array_value(config, "POSICIONES_ENTRENADORES");
	config_team -> pokemon_entrenadores = (t_lista_lista_pokemons*) config_get_array_value(config, "POKEMON_ENTRENADORES");
	config_team -> objetivos_entrenadores = (t_lista_lista_pokemons*) config_get_array_value(config, "OBJETIVOS_ENTRENADORES");
	config_team -> tiempo_reconexion = config_get_int_value(config, "TIEMPO_RECONEXION");
	config_team -> retardo_cpu = config_get_int_value(config, "RETARDO_CICLO_CPU");
	config_team -> algoritmo_planificacion = strdup(config_get_string_value(config, "ALGORITMO_PLANIFICACION"));
	config_team -> ip_broker = strdup(config_get_string_value(config, "IP_BROKER"));
	config_team -> puerto_broker = strdup(config_get_string_value(config, "PUERTO_BROKER"));
	config_team -> estimacion_inicial = config_get_int_value(config, "ESTIMACION_INICIAL");
	config_team -> log_path = strdup(config_get_string_value(config, "LOG_FILE"));

	config_destroy(config);

}

void liberar_config(t_config_team* config) {
	free(config -> algoritmo_planificacion);
	free(config -> log_path);
	free(config -> ip_broker);
	free(config -> puerto_broker);
	free(config);
}

void terminar_programa(int conexion,t_log* logger,t_config_team* config) {
	liberar_config(config);
	liberar_logger(logger);
	liberar_conexion(conexion);
}
