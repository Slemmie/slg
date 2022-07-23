// error shorthands

#pragma once

// initialize things
void init_errors();

// prints error message to stderr and exits with non-zero code
void fatal_error(const char* format, ...);

// same as fatal_error, but strictly for internal errors
void internal_fatal_error(const char* format, ...);
