// implements compile.h

#include "compile.h"

#include "compilation_preprocessing.h"
#include "util/file_io.h"

void compile(const char* input_file_path, const char* output_file_path) {
	// read input file into buffer
	char* input_buffer = read_file(input_file_path);
	
	// perform preprocessing
	// make sure bracket sequences are balanced
	check_balanced_brackets(input_buffer);
	// change all char const expressions inside "'" to raw numbers,
	// also check whether "'" contains incorrect sequences
	replace_charconstexpr(&input_buffer);
	
	// tokenize
	
	// generate output buffer from token list by individually parsing every function
	char* output_buffer = create_asm_file(/* token list, ... */);
	
	// write buffer to output file
	write_file(output_file_path, output_buffer);
}
