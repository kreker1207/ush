#include "../inc/ush.h"
char **comands_names = (char *[]){"cd", "echo", "env", "exit", "export", "fg", "pwd", "unset", "which", NULL};


//Передаем строку, введенную пользователем
void mx_proccess_line(char *line, t_envvar *vble) {
    
    char **splited_line_by_semicolumn = mx_strsplit(line, ';');

    
    for (int i = 0; splited_line_by_semicolumn[i] != NULL; i++) {
    
        splited_line_by_semicolumn[i] = mx_strtrim(splited_line_by_semicolumn[i]);
    //delet extra spaces
    }

    for (int i = 0; splited_line_by_semicolumn[i] != NULL; i++) {
        wordexp_t p_env;
        ///process spliting
        splited_line_by_semicolumn[i] = mx_replace_substr(splited_line_by_semicolumn[i], "$?", getenv("?"));
        
        if (getenv("OLDPWD")) {
            splited_line_by_semicolumn[i] = mx_replace_substr(splited_line_by_semicolumn[i], "${OLDPWD}", getenv("OLDPWD"));
            splited_line_by_semicolumn[i] = mx_replace_substr(splited_line_by_semicolumn[i], "$OLDPWD", getenv("OLDPWD"));
        } else {
            splited_line_by_semicolumn[i] = mx_replace_substr(splited_line_by_semicolumn[i], "${OLDPWD}", "");
            splited_line_by_semicolumn[i] = mx_replace_substr(splited_line_by_semicolumn[i], "$OLDPWD", "");
        }

        if (wordexp(splited_line_by_semicolumn[i], &p_env, 0)) {
            mx_printerr("ush: bad substitution\n");
            setenv("?", "1", 1);
            continue;
        }
        int g;
        int size = 0;
        char **term_arg_cmd = 0;
        for (int i = 0; p_env.we_wordv[i]; i++) {
            if (strcmp(p_env.we_wordv[i], "dumb")) {
                term_arg_cmd = push_back_str(term_arg_cmd, &size, p_env.we_wordv[i]);
            }
        }
        for(g = 0; g < 10; g++ ) {
            /////was function to check 
            g= g + 1;
        }
        
        if (mx_binary_search(comands_names, mx_arrsize(comands_names), term_arg_cmd[0]) != -1         /*is_own_command(term_arg_cmd[0])*/) {
            proccess_own_command(term_arg_cmd, vble);
        } else {
            proccess_system_command(term_arg_cmd);
        }

        wordfree(&p_env);
        mx_del_strarr(&term_arg_cmd);
    }
}
