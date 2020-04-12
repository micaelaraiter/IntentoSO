/*
 * Cliente.h
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#ifndef GAMECARD_H_
#define GAMECARD_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"


t_log* iniciar_logger(void);
t_config_broker leer_config(void);
void terminar_programa(int, t_log*, t_config*);

typedef struct {
	int conexion;
    int sizeMemoria;
	int sizeMinMemoria;
	char* algoritmoMemoria;
	char* algoritmoReemplazo;
	char* algoritmoParticionLibre;
	char* ip;
	char* puerto;
	int frecuenciaCompactacion;
} t_config_broker;

#endif /* GAMECARD_H_ */