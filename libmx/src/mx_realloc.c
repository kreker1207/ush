#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    size_t current;
    void *new;

    if (ptr == 0) {
        return malloc(size);
    }

    current = malloc_size(ptr);

    if (size <= current) {
        return ptr;
    }
	    
    new = malloc(size);
    mx_memcpy(new, ptr, current);
    free(ptr);
    return new;
}
