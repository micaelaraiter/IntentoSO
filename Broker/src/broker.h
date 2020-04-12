#ifndef GAMECARD_H_
#define GAMECARD_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

typedef struct {
	int conexion;
    int sizeMemoria;
	int sizeMinMemoria;
	char* algoritmoMemoria;
	char* algoritmoReemplazo;
	char* algoritmoParticionLibre;
	char* ip_team;
	char* puerto_team;
	char* ip_gamecard;
	char* puerto_gamecard;
	int frecuenciaCompactacion;
} t_config_broker;

t_log* iniciar_logger(void);
t_config_broker* leer_config(t_log* logger);
void terminar_programa(int, int, t_log*, t_config_broker*);

#endif /* GAMECARD_H_ */
