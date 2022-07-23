// utility for generating random data

#pragma once

#include <stdint.h>
#include <stddef.h>

// generate random unsigned 32 bit integer in the range [from, to]
uint32_t get_rand_uint32(uint32_t from, uint32_t to);

// generate random hex string of given length
// [0123456789abcdef]
char* get_rand_rex_str(size_t length);
