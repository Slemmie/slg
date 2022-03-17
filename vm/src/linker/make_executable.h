// make the final executable

#pragma once

#include <stdint.h>
#include <stddef.h>

struct Symbol_list;

uint8_t* make_executable(Symbol_list* symbol_list, void** binaries, size_t input_count, size_t* result_length);
