#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int index = 0;

    if (str != NULL && sub != NULL) {
        while (*str) {
            if (!mx_strncmp (str, sub, mx_strlen(sub))) {
                return index;
            }
            str++;
            index++;
        }
        return -1;
    }
    return -2;
}
