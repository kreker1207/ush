#include "../inc/libmx.h"

int mx_arrsize (char **arr) {
    int len = 0;
    while (arr[len] != NULL) {
        len++;
    }
    return len;
}
