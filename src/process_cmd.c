#include "../inc/ush.h"

void proccess_own_command(char **term_arg_cmd, t_envvar *vble) {
    if (!strcmp(term_arg_cmd[0], "cd")) {
        mx_cd(term_arg_cmd, vble);
    }
    else if (!strcmp(term_arg_cmd[0], "pwd")) {
        mx_pwd(term_arg_cmd, vble);
    }
    else if (!strcmp(term_arg_cmd[0], "env")) {
        mx_env(term_arg_cmd);
    }
    
     else if (!strcmp(term_arg_cmd[0], "echo")) {
        mx_echo(term_arg_cmd);
    }
    else if (!strcmp(term_arg_cmd[0], "which")) {
        mx_which(term_arg_cmd);
    }
   
    else if (!strcmp(term_arg_cmd[0], "export")) {
        mx_export(term_arg_cmd);
    }
    else if (!strcmp(term_arg_cmd[0], "unset")) {
        mx_unset(term_arg_cmd);
    }
    else if (!strcmp(term_arg_cmd[0], "exit")) {
        mx_exit(term_arg_cmd);
    }
}
