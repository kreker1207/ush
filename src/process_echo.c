#include "../inc/ush.h"
char *process_slashes(char *str) {
    char *res = (char *)malloc(mx_strlen(str) + 1);
    int len = 0;

    for (int i = 0; i <= mx_strlen(str); i++) {
        if (str[i] == '\\' && str[i + 1] == '\\') {
            i++;
        }
        if (str[i] == '\\' && str[i + 1] == 'e') {
            if (str[i + 2] != '\\') {
                (i) += 3;
            }
            else {
                (i) += 2;
            }
        }
        res[len] = str[i];
        len++;
    }
    res[len] = '\0';
    return res;
}

char *process_incomands(char *arg, t_for_echo echo) {
    char *include_cmd[] = {"\\a","\\b","\\f","\\n","\\r","\\t","\\v", NULL};
    char *final[] = {"\a","\b","\f","\n","\r","\t","\v", NULL};
    char *res = mx_strnew(ARG_MAX);
    int index = 0;
    if ((index = mx_get_substr_index(arg, "\\c")) >= 0) {
        strncpy(res, arg, index);
        echo.n = true;
    }
    else {
        strcpy(res, arg);
    }
    char *tmp = process_slashes(res);
    for (int i = 0; include_cmd[i] != NULL; i++) {
        if (strstr(tmp, include_cmd[i])) {
            tmp = mx_replace_substr(tmp, include_cmd[i], final[i]);
        }
    }
    free(res);
    return tmp;
}

