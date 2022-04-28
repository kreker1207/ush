#include "../inc/ush.h"

extern char **environ;

void mx_export(char **term_arg_cmd) {
    int size = mx_arrsize(term_arg_cmd);
    if (size == 1) {
        int env_size = 0; ////redone
        char **env = 0;
        char **p_env = environ;
        while (*p_env) {
            char *str = strdup(*p_env);
            /*

switch (type)
    {
    case 1:
        for(int i = 2; i < argc; i++ ) {
            str = argv[i];
            mx_printstr(str);
            if(argv[i+1] != NULL) {
              mx_printstr(" ");  
            }
        }
        break;
    case 2:
    
        for(int i = 2; i< argc; i++) {
            printf("ebann");
            dst = mx_strcpy(argv[i],dst);
            
            char* buf = dst;

            if(dst[0] != '\"') {
                mx_printstr(dst);
                mx_printstr(" ");
            }
            




            */
            int j = mx_get_char_index(str, '=');
            char **value = mx_strsplit(&str[j + 1], ' ');
            if (!*value) {
                str = mx_strjoin(str, "\'\'");
            } else if (mx_arrsize(value) > 1) {
                char *temp = str;
                str = strndup(temp, j + 1);
                str = mx_strjoin(str, "\'");
                str = mx_strjoin(str, &temp[j + 1]);
                str = mx_strjoin(str, "\'");
                free(temp);
            }
            
            env = push_back_str(env, &env_size, str);
            p_env++;
            free(str);
            free(value);
        }
        quick_sort_char_arr(env, 0, env_size - 1);
        for (int i = 0; i < env_size; i++) {
            printf("%s\n", env[i]);
        }
    } else {
        int i = 1, j;
        while (i < size && (j = mx_get_char_index(term_arg_cmd[i], '=')) != -1) {
            char *argv_name = strndup(term_arg_cmd[i], j);
            char *value = strdup(&term_arg_cmd[i][j + 1]);
            setenv(argv_name, value, 1);
            free(argv_name);
            free(value);
            i++;
        }
    }
}
