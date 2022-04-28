#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *newstr = NULL;
    size_t size = mx_strlen(s1);

    if (n < size) {
        size = n;
    } 

    newstr = mx_strnew(size);
    mx_strncpy(newstr, s1, size);
    
    return newstr;
}
