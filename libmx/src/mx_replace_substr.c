#include "../inc/libmx.h"

char *mx_replace_substr(char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace) {
        return NULL;
    }
    
    if (!mx_count_substr(str, sub)) return str;
    
    int sum = mx_strlen(replace) - mx_strlen(sub);
    int len = mx_strlen(str) + mx_count_substr(str, sub) * sum;
    char *memory = mx_strnew(len);
    
    char *p = str;
    for (int i = 0; *p; i++) {
        if (!mx_strncmp((char *)p, (char *)sub, mx_strlen(sub)) && *p != '\0') {
            p += mx_strlen(sub);
            for (int j = 0; j < mx_strlen(replace); i++, j++) {
                memory[i] = replace[j];
            }
            i--;
        }
        else {
            memory[i] = *p;
            p++;
        }
    }
    free(str);
    return memory;
}
