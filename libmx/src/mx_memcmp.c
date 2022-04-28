#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    if (n == 0) {
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
		if (((const unsigned char *)s1)[i] != ((const unsigned char *)s2)[i]) {
			return ((const unsigned char *)s1)[i] - ((const unsigned char *)s2)[i];
	    }
    }
    return 0;
}
