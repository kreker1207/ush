#include "../inc/libmx.h"

void mx_printerrchar(char c) {
    write(2, &c, 1);
}
