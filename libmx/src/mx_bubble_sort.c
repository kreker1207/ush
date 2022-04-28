#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) 
{   int amount = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int j = size - 1; j > i ; j--) {
            if (mx_strcmp(arr[j - 1], arr[j]) > 0) {
                amount++;
                char *temp = arr[j - 1];
                arr [j - 1] = arr [j];
                arr [j] = temp;
            }
        }
    }
    return amount;
}
