#include "../inc/libmx.h"

void quick_sort_char_arr(char **arr, int left, int right) {
    if (left < right) {
        char *mid = arr[(left + right) / 2];
        int i = left, j = right;

        while (i <= j) {
            while(mx_strcmp(arr[i], mid) < 0) i++;
            while(mx_strcmp(arr[j], mid) > 0) j--;

            if (i <= j) {
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                
                i++;
                j--;
            }
        }

        quick_sort_char_arr(arr, left, j);
        quick_sort_char_arr(arr, i, right);
    }
}
