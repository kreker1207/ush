#include "../inc/libmx.h"

void mx_printint(int n) {

	if (n == -2147483648) {
		write(1, "-2147483648", 11);
		return;
	}

	if (n < 0) {
		mx_printchar('-');
        n *= -1;
	}

	if (n == 0) {
		mx_printchar('0');
	}

	int length = 0, temp_n = n;

	while (temp_n != 0) {
		temp_n /= 10;
		length++;
	}

	char array[length];

	for (int i = 0; i < length; i++) {
		int d = n % 10;
		array[i] = d + 48;
		n /= 10;
	}

	for(int i = length - 1; i >= 0; i--) {
		mx_printchar(array[i]);
	}
}
