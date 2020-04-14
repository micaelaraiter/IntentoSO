
#ifndef GAMECARD_H_
#define GAMECARD_H_
//Por qué GAMECARD_H_? Está en todos los .h
#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

typedef struct {
    int tiempoReintentoConexion;
	int tiempoReintentoOperacion;
	char* puntoMontajeTallgras;
	char* ipBroker;
	char* puertoBroker;
} t_config_team;


t_log* iniciar_logger(void);
t_config_team* leer_config(void);
void terminar_programa(int, t_log*, t_config*);

#endif /* GAMECARD_H_ */
