#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include<utils.h>


t_log* logger;
t_log* iniciar_logger(void);
t_config_game_card* leer_config(void);
void terminar_programa(int, t_log*, t_config_game_card*);
void liberar_conexion(int);
void liberar_logger(t_log* logger);
void liberar_config_game_card(t_config_game_card*);
