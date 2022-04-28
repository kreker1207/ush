#include "../inc/libmx.h"

char *mx_strjoin(char *s1, char const *s2) {
    if (s1 == NULL && s2 == NULL) {
        return NULL;
    }

    if (s1 == NULL) {
        return mx_strdup(s2);
    }

    if (s2 == NULL) {
        return mx_strdup(s1);
    }

    char *joined = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    mx_strcat(joined, s1);
    mx_strcat(joined, s2);
    free(s1);
    return joined;
}
