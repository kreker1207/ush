#include "../inc/libmx.h"

static void swap_char(char *s1, char *s2) {
    char temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

static void str_reverse(char *s, int length) {
    for (char *end = s + length - 1; end > s; --end) {
        swap_char(s, end);
        ++s;
    }
}

char *mx_nbr_to_hex(unsigned long nbr) {
    char* number = mx_strnew(12);  // 12 - max long HEX digits count.
    int digit_it = 0;  // Digit iterator.
    int digit;
    if (number == NULL) {
        return NULL;
    }
    if (nbr == 0) {
        *number = '0';
        return number;
    }
    while (nbr != 0) {
        digit = nbr % 16;
        number[digit_it] = digit;
        number[digit_it++] += digit <= 9 ? '0' : 'a' - 10;
        nbr /= 16;
    }
    str_reverse(number, digit_it);
    return number;
}
