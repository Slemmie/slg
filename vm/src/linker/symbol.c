// implementations of symbol.h functions

#include "symbol.h"

#include "../util/token_type.h"
#include "../util/exit_codes.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// create a list of symbols from a series of binaries
Symbol_list create_symbol_list(void** binaries, size_t count) {
	// look for all instances of TOK_LABEL
	
	// first count the required length of a Symbol_list
	// assume a valid series of tokens in the binaries
	size_t symbol_def_count = 0;
	size_t start_function = ~0;
	for (size_t i = 0; i < count; i++) {
		size_t length = (size_t) (*((uint64_t*) binaries[i]));
		for (size_t j = 8; j < length; ) {
			Token_type token = (Token_type) ((uint8_t*) binaries[i])[j];
			// if the token is a TOK_LABEL, add to the list size
			if (token == TOK_LABEL) {
				symbol_def_count++;
				j++; // skip the TOK_SYMBOL token
				// get the string
				size_t str_length = (size_t) *((uint64_t*) ((uint8_t*) (binaries[i]) + j));
				j += 8;
				char* str = malloc(sizeof(char) * (str_length + 1));
				// check if malloc failed
				if (!str) {
					printf("[fatal error]: malloc failed\n");
					exit(SLG_EXIT_INTERNAL_ERROR);
				}
				// fill the buffer
				for (size_t k = 0; k < str_length; k++, j++) {
					str[k] = ((uint8_t*) binaries[i])[j];
				}
				str[str_length] = '\0';
				// check if it is the start label
				if (!strcmp(str, "start")) {
					start_function = symbol_def_count - 1;
				}
				// TODO: check for mutliple definition error
				free(str);
				continue;
			}
			// go further
			// we assume the file cannot end right after a TOK_LABEL
			// so we are allowed to continue above, and immediately check for token == TOK_LABEL again
			null_incr_binary_ptr(binaries[i], &j);
		}
	}
	
	// create object
	Symbol_list result;
	result.size = symbol_def_count;
	result.symbols = malloc(sizeof(Symbol) * symbol_def_count);
	
	size_t index = 0;
	for (size_t i = 0; i < count; i++) {
		size_t length = (size_t) (*((uint64_t*) binaries[i]));
		for (size_t j = 8; j < length; ) {
			Token_type token = (Token_type) ((uint8_t*) binaries[i])[j];
			// if the token is a TOK_LABEL, make a symbol object
			if (token == TOK_LABEL) {
				j++; // skip the TOK_SYMBOL token
				// get the string length
				size_t str_length = (size_t) *((uint64_t*) ((uint8_t*) (binaries[i]) + j));
				j += 8; // now point to the string
				// make the object
				result.symbols[index].length = str_length;
				result.symbols[index++].name = (char*) (((uint8_t*) binaries[i]) + j);
				// finally set pointer to the end of the string before moving on
				j += str_length;
				continue;
			}
			// go further
			null_incr_binary_ptr(binaries[i], &j);
		}
	}
	
	return result;
}

// destruct a list of symbols
void destruct_symbol_list(Symbol_list* symbol_list) {
	if (symbol_list->symbols) {
		free(symbol_list->symbols);
		symbol_list->symbols = NULL;
		symbol_list->size = 0;
	}
}
