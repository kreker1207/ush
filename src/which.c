#include "../inc/ush.h"

    char **MX_BUILT_IN_COMAND = (char*[]) {"alias", "bg", "cd", "chdir", "echo", "env", "exit", "export",\
                            "false", "fg", "jobs", "kill", "pwd", "true", "unset", "which"};

bool is_builtin_command(char *cmd) {
    return mx_binary_search(MX_BUILT_IN_COMAND, mx_arrsize(MX_BUILT_IN_COMAND), cmd) != -1;
}

/*

DIR *dir;
    struct dirent *dent;
        for (int j = 0; j < counter; j++ ) {
            if((dir = opendir(ways[j])) != NULL)
            {
                while((dent=readdir(dir))!=NULL) {
                    if(mx_strcmp(argv,dent->d_name) == 0) {
                        
                        mx_printstr(ways[j]);
                        mx_printstr("/");
                        mx_printstr(argv);
                        mx_printstr("\n");
                        if(type == 1){
                            break;
                        }
                    }
                }
            }
        }
        
    closedir(dir);

*/
void mx_which(char **term_arg_cmd) {
    setenv("?", "0", 1);
    int i = 1;
    t_for_which flags = {false, false};
    while (term_arg_cmd[i] && term_arg_cmd[i][0] == '-') {
        if (!strcmp(term_arg_cmd[i], "-a")) {
            flags.a = true;
        } else if (!strcmp(term_arg_cmd[i], "-s")) {
            flags.s = true;
        } else {
            mx_printerr("which: bad option: ");
            mx_printerr(term_arg_cmd[i]);
            mx_printerr("\n");
            setenv("?", "1", 1);
        }
        i++;
    }
    
    while (term_arg_cmd[i]) {
        bool is_builtin = is_builtin_command(term_arg_cmd[i]);
        char *path = find_command_path(term_arg_cmd[i]);
        if (path) {
            int j = mx_get_char_index(path, '/');
            while(mx_get_char_index(&path[j + 1], '/') != -1) {
                j += mx_get_char_index(&path[j + 1], '/') + 1;
            }
            char *cmd = strdup(&path[j + 1]);
            if (is_builtin) {
                printf("%s: ush built-in cmd\n", cmd);
                if (flags.a && !flags.s) {
                    printf("%s\n", path);
                }
            } else if (!flags.s) {
                printf("%s\n", path);
            }
            free(cmd);
            free(path);
        } else {
            if (is_builtin) {
                printf("%s: ush built-in cmd\n", term_arg_cmd[i]);
            } else {
                mx_printerr(term_arg_cmd[i]);
                mx_printerr(" not found\n");
                setenv("?", "1", 1);
            }
        }
        i++;
    }
}
