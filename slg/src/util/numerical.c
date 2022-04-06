// implements util/numerical.h

#include "numerical.h"

#include <assert.h>
#include <stddef.h>

int digit_count(long long value) {
	int result = value < 0LL;
	
	value *= value < 0LL ? -1 : 1;
	
	do {
		result++;
	} while (value /= 10);
	
	return value;
}

void iota(long long value, char* buffer, int base) {
	assert(base >= 2 && base <= 16);
	assert(buffer);
	
	size_t ptr = 0;
	if (value < 0LL) {
		buffer[ptr++] = '-';
		value *= -1;
	}
	
	const char str_base_convert[] = "0123456789abcdef";
	
	do {
		buffer[ptr++] = str_base_convert[value % base];
	} while (value /= base);
	
	buffer[ptr] = '\0';
}
