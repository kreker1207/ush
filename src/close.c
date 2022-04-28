#include "../inc/ush.h"

void exit_proccess (char *exit_code) { 
    int code = mx_atoi(exit_code);

    if (!strcmp(exit_code, "0")) {
        exit(0);
    }
    else {
        exit(code);
    }
}

void mx_exit (char **term_arg_cmd) {
    if (!term_arg_cmd) exit(1);
    int size = mx_arrsize(term_arg_cmd);
    switch (size) {
        case 1:
            exit(1);
            break;
        case 2:
            exit_proccess(term_arg_cmd[1]);
            break;
        default:
            mx_printerr("exit: too many arguments\n");
            break;
    }
}

