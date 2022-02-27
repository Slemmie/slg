// read a variable number of binaries and return a list of buffers

#pragma once

#include <stddef.h>

// does not handle error printing
// returns NULL if an error occurred
void** read_binaries(const char** filepaths, size_t count);
