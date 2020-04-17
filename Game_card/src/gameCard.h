#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

t_log* logger;
t_log* iniciar_logger(void);
t_config_gameCard* leer_config(void);
void terminar_programa(int, t_log*, t_config_gameCard*);
void liberar_conexion(int);
void liberar_logger(t_log* logger);
void liberar_config(t_config_gameCard*);