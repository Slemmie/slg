// implements error.h

#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void fatal_error(const char* format, ...) {
	fprintf(stderr, "slg: \033[31mfatal error\033[0m: ");
	
	va_list arg;
	va_start(arg, format);
	vfprintf(stderr, format, arg);
	va_end(arg);
	
	fprintf(stderr, "\n");
	
	exit(EXIT_FAILURE);
}
