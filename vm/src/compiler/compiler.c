// implementation of int compile(const char*, const char*)

#include "../util/read_file.h"
#include "../util/exit_codes.h"

#include <stdio.h>

int compile(const char* output_file, const char* input_file) {
	// aquire source code from input_file
	char* source_code = read_source(input_file);
	
	// check if some error occoured while reading source code from input_file
	if (!source_code) {
		printf("[fatal error]: failed to read input file '%s'\n", input_file);
		exit(SLG_EXIT_FILE_ERROR);
	}
	
	return 0;
}
