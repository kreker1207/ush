#include "../inc/ush.h"


int check_argv(char **term_arg_cmd) {
    for (int i = 0; term_arg_cmd[i] != NULL; i++) {
        if (term_arg_cmd[i] && term_arg_cmd[i][0] == '-' && term_arg_cmd[i][1]) {
            mx_printerr("unset: bad option: -");
            mx_printerrchar(term_arg_cmd[i][1]);
            mx_printerr("\n");
            return 1;
        }
        if (term_arg_cmd[i] && term_arg_cmd[i][0] == '-' && !term_arg_cmd[i][1]) {
            mx_printerr("unset: not enough arguments\n");
            return 1; 
        }
    }
    return 0;
}

void mx_unset(char **term_arg_cmd) {
    if (check_argv (term_arg_cmd) == 1) {
        return;
    }
    for (int i = 1; term_arg_cmd[i] != NULL; i++) {
        unsetenv(term_arg_cmd[i]);
    }
}
/*
void unset_proccess (const char *var_name) {
    unsetenv(var_name);
}*/

