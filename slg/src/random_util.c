// implements random_util.h

#include "random_util.h"

#include "error.h"

#include <assert.h>
#include <time.h>
#include <stdlib.h>

long _get_time_nano() {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return ts.tv_nsec;
}

void _init_rand() {
	static int first_call = 1;
	
	// reset seed on first call plus every now and then
	if (first_call || ((_get_time_nano() % 27) & 1)) {
		first_call = 0;
		
		srand((unsigned int) (_get_time_nano() ^ _get_time_nano()));
	}
}

uint32_t get_rand_uint32(uint32_t from, uint32_t to) {
	assert(from <= to);
	
	_init_rand();
	
	uint32_t result = 0;
	
	for (uint32_t i = 0; i <= 31 - 5; i++) {
		_init_rand();
		uint32_t now = rand() % 0b11111;
		result ^= now << i;
	}
	
	return result % (to - from + 1) + from;
}

char* get_rand_rex_str(size_t length) {
	char* result;
	
	result = malloc(sizeof(char) * (length + 1));
	
	if (!result) {
		internal_fatal_error("malloc failed");
	}
	
	static const char idx_to_char[] = "0123456789abcdef";
	
	for (size_t i = 0; i < length; i++) {
		result[i] = idx_to_char[get_rand_uint32(0, 15)];
	}
	
	result[length] = '\0';
	
	return result;
}
