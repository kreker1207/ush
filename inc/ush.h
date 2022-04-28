#ifndef USH_H
#define USH_H

#include "../libmx/inc/libmx.h"
#include "../inc/ushstruct.h"
//
#include <cpio.h>//магические числа для формата архива cpio
#include <dirent.h> // откритие и вывод каталогов
#include <fcntl.h> //открытие файла/ блокировка и др 
#include <grp.h>// информация о пользовапельских группах и управления 
#include <pwd.h>// пользовательская информация и контроль 
#include <sys/ipc.h>// межпроцесное взаимодействие 
#include <sys/msg.h>// потоки сообщений
#include <sys/sem.h>// семафоры
#include <sys/stat.h>// информация о файле стат итд
#include <sys/time.h>// функции и стпуктуры работы со временем и датой
#include <sys/types.h>// различные типы данных
#include <sys/utsname.h>// аннейм и связные структуры
#include <sys/wait.h>//статус завершенных дочеерних процессов 
#include <tar.h>// магические числа для формата архивов тар
#include <termios.h>// позволяет использовать интерфейс терминала вывод-ввод
#include <unistd.h>// различные основные функции
#include <utime.h>//доступ и количевство модификаций 
#include <unistd.h>
//
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
//
#include <signal.h>
#include <wordexp.h>


char *process_incomands(char *arg, t_for_echo echo);
char *process_slashes(char *str);
void proccess_system_command(char **term_arg_cmd);
void mx_proccess_line(char *line, t_envvar *vble);
void proccess_own_command(char **term_arg_cmd, t_envvar *vble);

void mx_env(char **term_arg_cmd);
void mx_cd (char **term_arg_cmd, t_envvar *vble);
void mx_pwd(char **term_arg_cmd, t_envvar *vble);
void mx_which(char **term_arg_cmd);
void mx_unset(char **term_arg_cmd);
void mx_export(char **term_arg_cmd);
void mx_exit(char **term_arg_cmd);
void mx_echo(char **term_arg_cmd);



char *find_command_path(char *cmd);
char *manage_tilda (char *path);



char **manage_system_commands (char ***split_buffer);

char **push_back_str(char **arr, int *size, char *str);

#endif
