// error shorthands

#pragma once

#include <stddef.h>

// initialize things
void init_errors();

// allocate a pointer of desired length
// pointers given by this function are freed upon calling a terminating error function
// (after printing error message)
void* error_alloc(size_t bytes);

// prints error message to stderr and exits with non-zero code
void fatal_error(const char* format, ...);

// same as fatal_error, but strictly for internal errors
void internal_fatal_error(const char* format, ...);
