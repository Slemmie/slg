// implements compile.h

#include "compile.h"

void compile(const char* input_file_path, const char* output_file_path) {
	// read input file into buffer
	char* input_buffer = read_file(input_file_path);
	
	// perform preprocessing
	
	// tokenize
	
	// generate output buffer from token list by individually parsing every function
	char* output_buffer = create_asm_file(/* token list, ... */);
	
	// write buffer to output file
	write_file(output_file_path, output_buffer);
}
