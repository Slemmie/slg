// implementation of int compile(const char*, const char*)

#include "../util/read_file.h"

#include <stdio.h>

int compile(const char* output_file, const char* input_file) {
	// aquire source code from input_file
	char* source_code = read_source(input_file);
	
	return 0;
}
