#include "../inc/ush.h"

void ctrl_c_signal() {
    printf("\n");
}

int main() {
    //exit status is set by setenv
    setenv("?", "0", 1);
    setenv("OLDPWD", getenv("PWD"), 1);
    t_envvar vble = {getenv("PWD"), getenv("PWD"), getenv("HOME")};
    
    char line[1024];

    while (true) {
        errno = 0;

        sigaction(SIGINT, &(struct sigaction){ .sa_handler = ctrl_c_signal }, NULL);

        write(0, "u$h> ", 5);

        if (!fgets(line, 1024, stdin)) {
            if (errno == EINTR) continue;
            printf("exit\n");
            return 0;
        }

        mx_proccess_line(line, &vble);
    }
    return 0;
}
 
