#include "../inc/libmx.h" 

void *mx_memrchr(const void *s, int c, size_t n) {
	unsigned char *pointer = (unsigned char *)s + mx_strlen(s);

    for (int i = n; n > 0; i++, pointer--) {
        if (*pointer == (unsigned char)c) {
            return pointer;
        }
    }

	return NULL;
}
