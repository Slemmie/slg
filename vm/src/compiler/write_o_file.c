// implementation of going from token list to .o file

#include "write_o_file.h"

#include "../util/exit_codes.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// take a path to the output file along with a token list and generate a .o format file
void write_o_file(const char* output_file, Token_list* token_list) {
	// truncate and open for writing binary
	FILE* outfile = fopen(output_file, "wb");
	// make sure it opened
	if (!outfile) {
		printf("[fatal error]: failed to open file '%s' for writing", output_file);
		exit(SLG_EXIT_FILE_ERROR);
	}
	
	for (size_t i = 0; i < token_list->size; i++) {
		// use a single byte for printing the type of token
		uint8_t tok_type = (uint8_t) token_list->tokens[i].type;
		fwrite(&tok_type, sizeof(uint8_t), 1, outfile);
		// check if we should print the number as well
		if (token_list->tokens[i].type == TOK_NUMBER) {
			fwrite(&token_list->tokens[i].data, sizeof(uint64_t), 1, outfile);
		}
		if (token_list->tokens[i].type == TOK_SYMBOL) {
			fwrite(&token_list->tokens[i].data, sizeof(uint64_t), 1, outfile);
			// additionally, print the symbol name as a string of the length we just printed
			fwrite(token_list->tokens[i].symbol, sizeof(char), token_list->tokens[i].data, outfile);
		}
	}
	
	fclose(outfile);
}
