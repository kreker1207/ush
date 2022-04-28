#include "../inc/ush.h"

void proccess_system_command(char **term_arg_cmd) {
    char *path = find_command_path(term_arg_cmd[0]);
    if (path) {
        int pid = fork();
        if (!pid) {
            execv(path, term_arg_cmd);
            mx_printerr("ush: ");
            perror(path);
            return;
        } else {
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("ush");
                setenv("?", "1", 1);
                return;
            }
            
            setenv("?", mx_itoa(WEXITSTATUS(status)), 1);
        }
    } else {
        if (errno == EACCES) {
            mx_printerr("ush: permission denied: ");
            mx_printerr(term_arg_cmd[0]);
            mx_printerr("\n");
            setenv("?", "126", 1);
            return;
        } else if (errno == ENOTDIR) {
            mx_printerr("ush: not a directory: ");
            mx_printerr(term_arg_cmd[0]);
            mx_printerr("\n");
        } else if (term_arg_cmd[0][0] == '/') {
            mx_printerr("ush: no such file or directory: ");
            mx_printerr(term_arg_cmd[0]);
            mx_printerr("\n");
        } else {
            mx_printerr("ush: cmd not found: ");
            mx_printerr(term_arg_cmd[0]);
            mx_printerr("\n");
        }
        setenv("?", "127", 1);
    }
}
