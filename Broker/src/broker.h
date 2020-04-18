
#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include<utils.c>
#include<utils.h>


t_log* logger;
t_log* iniciar_logger(void);
t_config_broker* leer_config(void);
void terminar_programa(t_log*, t_config_broker*);
