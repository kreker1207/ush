#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s) {
    int l = 0, r = size - 1;
    
    while (l <= r) {
        int mid = (l + r) / 2;
        if (mx_strcmp(arr[mid], s) < 0) {
            l = mid + 1;
        } else if (mx_strcmp(arr[mid], s) > 0) {
            r = mid - 1;
        } else {
            return mid;
        }
    }
    
    return -1;
}
