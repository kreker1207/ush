#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (hex == NULL) {
        return 0;
    }

    unsigned long base = 1;
    unsigned long decimal = 0;
    int length = 0;

    while (hex[length] != '\0') {
        length++;
    }

    for(int i = length; i >= 0; i--) {
        if(mx_isdigit(hex[i])) {
            decimal = decimal + (hex[i] - 48) * base;
            base *= 16;
        }

        else if (mx_isalpha(hex[i])) {
            if (mx_isupper(hex[i])) {
                decimal = decimal + (hex[i] - 55) * base;
                base *= 16;
            }
            else if (mx_islower(hex[i])) {
                decimal = decimal + (hex[i] - 87) * base;
                base *= 16;
            }
        }
    }

    return decimal;
}
