#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (!arr) {
        return -1;
    } 

    int amount = 0;

    if (left < right) {

        int first = left;
        int last = right;
        char *pivot = arr[(last + first) / 2];

        while (first <= last) {
            while (mx_strlen(arr[first]) < mx_strlen(pivot)) {
                first++; 
            }
            while (mx_strlen(arr[last]) > mx_strlen(pivot)) {
                last--;
            }

            if (first <= last) {
                if (mx_strlen(arr[last]) != mx_strlen(arr[first])) {
                    char *temp = arr[first];
                    arr[first] = arr[last];
                    arr[last] = temp;
                    amount++;
                }
                last--;
                first++;
            }
        }

        amount += mx_quicksort(arr, left, last);
        amount += mx_quicksort(arr, first, right);
    }    
    return amount;
}
