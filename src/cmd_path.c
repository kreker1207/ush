#include "../inc/ush.h"

char *find_command_path(char *cmd) {
    if (cmd[0] == '/') {
        DIR *dir = opendir(cmd);
        if (!dir) {
            if (errno == ENOTDIR && !access(cmd, F_OK)) {
                return strdup(cmd);
            }
            return NULL;
        }
        execvp(cmd, NULL);
        closedir(dir);
        return NULL;
    }
    
    char **paths = mx_strsplit(getenv("PATH"), ':');
    if (!paths) {
        return NULL;
    }
    for (int i = 0; paths[i] != NULL; i++) {
        char *whole_pth = strdup(paths[i]);
        whole_pth = mx_strjoin(whole_pth, "/");
        whole_pth = mx_strjoin(whole_pth, cmd);
        struct stat st;
        if (!stat(whole_pth, &st)) {
            return whole_pth;
        }
        free(whole_pth);
    }
    
    mx_del_strarr(&paths);
    return NULL;
}
