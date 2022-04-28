#include "../inc/libmx.h"

char *mx_itoa(int number) {
    int length = 0;
    char * result = NULL;
    int temp = number;
    while (temp) {
		temp /= 10;
		length++;
	}
    result = mx_strnew(length);
    if (number == -2147483648) {
		return mx_strcpy(result, "-2147483648");
    }
    if (number == 0) {
		return mx_strcpy(result, "0");
    }
    temp = number;
	for (int i = 0; i < length; i++) {
        if(temp < 0) {
            result[length] = '-';
            temp = -temp;
        }       
        result[i] = temp % 10 + 48;
        temp  /= 10 ;
    }
    mx_str_reverse(result);
    return result;
}
