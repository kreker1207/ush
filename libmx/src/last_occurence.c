#include "../inc/libmx.h"

int last_occurence(const char *str, char c) {
    if (!*str) {
        return -1;
    }
    int n = last_occurence(str + 1, c);
    return n + (n != -1 || *str == c);
}
