#include "../inc/ush.h"

char **push_back_str(char **arr, int *size, char *str) {
    char **new_arr = (char**)malloc(sizeof(char*) * ++(*size) + 1);
    for (int i = 0; i < *size - 1; i++) {
        new_arr[i] = mx_strdup(arr[i]);
    }
    new_arr[*size - 1] = mx_strdup(str);
    new_arr[*size] = 0;

    for (int i = 0; i < *size - 1; i++) {
        free(arr[i]);
    }
    free(arr);
    
    return new_arr;
}
