// implementation of int compile(const char*, const char*)

#include "../util/read_file.h"
#include "../util/exit_codes.h"

#include "token.h"
#include "write_o_file.h"

#include <stdio.h>

int compile(const char* output_file, const char* input_file) {
	// aquire source code from input_file
	char* source_code = read_source(input_file);
	
	// check if some error occoured while reading source code from input_file
	if (!source_code) {
		printf("[fatal error]: failed to read input file '%s'\n", input_file);
		exit(SLG_EXIT_FILE_ERROR);
	}
	
	// get parsed token list
	Token_list token_list = create_token_list(source_code);
	
	// create a binary file of instructions from the token list (write to output_file)
	write_o_file(output_file, &token_list);
	
	// free token list
	destruct_token_list(&token_list);
	
	// free source code buffer
	free(source_code);
	
	return 0;
}
