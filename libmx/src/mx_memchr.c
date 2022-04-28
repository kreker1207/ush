#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *pointer = (unsigned char *)s;

    for (size_t i = 0; i < n; i++) {
        if (*pointer == (unsigned char)c) {
            return pointer;
        }
        pointer++;
    }

	return NULL;
    
}
