#include "../inc/ush.h"

void read_flags(char flag, t_for_pwd *pwd) {
    switch (flag) {
        case 'P':      
            pwd->P = true;
            pwd->L = false;
            break;
        case 'L':
            pwd->L = true;
            pwd->P = false;
            break;
        default:
            mx_printerr("ush: pwd: bad option: -");
            mx_printerrchar(flag);
            mx_printerr("\n");
            pwd->error = true;
            setenv("?", "1", 1);
            break;
    }
}

void check_pwd_flags(char **term_arg_cmd, t_for_pwd *pwd) {
    for (int i = 1; term_arg_cmd[i] != NULL; i++) {
        if (pwd->error) {
            setenv("?", "1", 1);
            break;
        }
        if (mx_arrsize(term_arg_cmd) > i && term_arg_cmd[i][0] == '-') {
            for (int k = 1; term_arg_cmd[i][k] != '\0'; k++) {
                read_flags(term_arg_cmd[i][k], pwd);
                if (pwd->error) {
                    break;
                }
            }
            if (strcmp(term_arg_cmd[i], "-LP") && strcmp(term_arg_cmd[i], "-P") && strcmp(term_arg_cmd[i], "-L") && strcmp(term_arg_cmd[i], "-PL")) {
                pwd->L = false;
                pwd->P = false;
            }
        }
        else {
            pwd->L = true; //-L и буз флага - одно и тоже
        }
    }
}


void pwd_proccess(char *line, t_for_pwd pwd, t_envvar *vble) {
    if (line != NULL) {
        mx_printerr("pwd: too many arguments\n");
        setenv("?", "1", 1);
        return;
    }
    char *path_P = (char *)malloc(1024*sizeof(char));
    if (pwd.L) {
        printf("%s\n", vble->pwd);
    }
    else {
        printf("%s\n", getcwd(path_P, 1024));
    }
    free(path_P);
}


void mx_pwd (char **term_arg_cmd, t_envvar *vble) {
    setenv("?", "0", 1);
    t_for_pwd pwd = {true, false, false};

    check_pwd_flags (term_arg_cmd, &pwd);

    char *arg = NULL;
    for (int z = 1; term_arg_cmd[z] != NULL; z++) {
        if (!strcmp(term_arg_cmd[z], "-LP") || !strcmp(term_arg_cmd[z], "-P") || !strcmp(term_arg_cmd[z], "-L") || !strcmp(term_arg_cmd[z], "-PL") || term_arg_cmd[z][0] == '-') {
            continue;
        }
        else {
            if (arg != NULL) {
                arg = mx_strjoin(arg, term_arg_cmd[z]);
            }
            else {
                arg = strdup(term_arg_cmd[z]);
            }
            arg = mx_strjoin(arg, " ");
        }
        arg = mx_strtrim(arg);
    }
    if(!pwd.error) {
        pwd_proccess(arg, pwd, vble);
    }
    free(arg);
}
