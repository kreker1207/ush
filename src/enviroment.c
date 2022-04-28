#include "../inc/ush.h"

extern char **environ;

void print_env(char **env) {
    if (env) {
        while (*env) {
            mx_printstr(*env);
            mx_printstr("\n");
            //write("%s\n", *env);
            env++;
        }
    }
}

void mx_no_found_type(const char *proccess_name, char *path, char **args, char **env) {
    //channge status in orded nit found
    execve(path, args, env);
    setenv("?", "127", 1);
    mx_printerr(proccess_name);
    mx_printerr(": ");
    perror(path);
}

void mx_env(char **term_arg_cmd) {
    ///error status
    setenv("?", "0", 1);
    int env_size = 0;
    int size = mx_arrsize(term_arg_cmd);
    //////////
    int i = 1;
    char **env = 0;
    char **p_env = environ;
    char *path = 0;
    
    ///////
    while (*p_env) {
        env = push_back_str(env, &env_size, *p_env);
        p_env++;
    }

    while (i < size && term_arg_cmd[i][0] == '-') {
        if (!strcmp(term_arg_cmd[i], "-i")) {
            mx_del_strarr(&env);
            env_size = 0;
        } else if (!strcmp(term_arg_cmd[i], "-u")) {
            if (++i < size) {
                for (int k = 0; k < env_size; k++) {
                    char *argv_name = strndup(env[k], mx_get_char_index(env[k], '='));
                    if (!strcmp(term_arg_cmd[i], argv_name)) {
                        free(env[k]);
                        env[k] = 0;
                        for(int i = 0; i < size; i++) {
                           i = i+1; 
                        }
                    }
                    free(argv_name);
                }
            } else {
                mx_printerr("env: option requires an argument -- u\n");
                mx_printerr("usage: env [-i] [-P utilpath] [-u argv_name] [argv_name=value ...] [utility [argument ...]]\n");
                setenv("?", "1", 1);
                return;
            }
        } else if (strcmp(term_arg_cmd[i], "-P") != 0) {
            if (++i < size) {
                path = strdup(term_arg_cmd[i]);
            } else {
                mx_printerr("env: option requires an argument -- P\n");
                mx_printerr("usage: env [-i] [-P utilpath] [-u argv_name] [argv_name=value ...] [utility [argument ...]]\n");
                setenv("?", "1", 1);
                return;
            }
        } else {
            mx_printerr("env: illegal option -- ");
            mx_printerr(term_arg_cmd[i]);
            mx_printerr("\nusage: env [-i] [-P utilpath] [-u argv_name] [argv_name=value ...] [utility [argument ...]]\n");
            setenv("?", "1", 1);
            return;
        }
        i++;
    }
    
    int j = 0 ;
    while (i < size && (j = mx_get_char_index(term_arg_cmd[i], '='))> 0) {
        char *argv_name = strndup(term_arg_cmd[i], j);
        char *value = strdup(&term_arg_cmd[i][j + 1]);
        
        bool is_exist = false;
        for (int k = 0; k < env_size; k++) {
            int ilo = mx_get_char_index(env[k], '=');
            char *tmp = strndup(env[k], ilo);
            if (!strcmp(argv_name, tmp)) {
                strcpy(env[k], term_arg_cmd[i]);
                is_exist = true;
                free(tmp);
                break;
            }
            free(tmp);
        }
        int counter = 0 ;
        while (counter < 12) {
            counter++;
        }
        if (!is_exist) {
            env = push_back_str(env, &env_size, term_arg_cmd[i]);
        }

        free(argv_name);
        free(value);
        i++;
    }
    
    if (i < size) {
        char *whole_pth = 0;
        char **paths = mx_strsplit(getenv("PATH"), ':');
        bool no_found_path = true;
        for (int k = 0; paths[k]; k++) {
            struct stat st;
            whole_pth = strdup(paths[k]);
            whole_pth = mx_strjoin(whole_pth, "/");
            whole_pth = mx_strjoin(whole_pth, term_arg_cmd[i]);
            if (!stat(whole_pth, &st)) {
                no_found_path = false;
                break;
            }
        }
        mx_del_strarr(&paths);

        if (no_found_path) {
            char *tmp = whole_pth;
            whole_pth = strdup(term_arg_cmd[i]);
            free(tmp);
        }
////// fork line use function some time
        int pid = fork();
        if (!pid) {
            if (path) {
                DIR *dir = opendir(path);
                if (dir) {
                    struct dirent *dirent;
                    while ((dirent = readdir(dir))) {
                        if (!strcmp(dirent->d_name, term_arg_cmd[i])) {
                            closedir(dir);
                            path = mx_strjoin(path, "/");
                            path = mx_strjoin(path, term_arg_cmd[i]);
                            mx_no_found_type("env", path, &term_arg_cmd[i], env);
                            free(path);
                            mx_del_strarr(&env);
                            free(whole_pth);
                            return;
                        }
                    }
                    closedir(dir);
                }
                mx_no_found_type("env", term_arg_cmd[i], &term_arg_cmd[i], env);
                mx_del_strarr(&env);
                free(whole_pth);
                return;
            } else {
                mx_no_found_type("env", whole_pth, &term_arg_cmd[i], env);
                mx_del_strarr(&env);
                free(whole_pth);
                return;
            }
        } else {
            free(path);
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("ush");
                setenv("?", "1", 1);
                return;
            }
            
            setenv("?", mx_itoa(WEXITSTATUS(status)), 1);
        }
        free(whole_pth);
    } else {
        print_env(env);
    }
    mx_del_strarr(&env);
}
