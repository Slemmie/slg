// increment a pointer to the next token, without caring about what the token means
// for instance, if the token is TOK_NUMBER, we also want to read the actual number
// and increase the pointer accordingly

#pragma once

// NOTE! this function only works for .o files, not executable binaries!

#include <stddef.h>

void null_incr_binary_ptr(const void* binary, size_t* ptr);
