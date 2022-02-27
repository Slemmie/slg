// source file gets broken into a sequence of tokens

#pragma once

#include "../util/token_type.h"

#include <stddef.h>
#include <stdint.h>

// actual token
typedef struct {
	
	Token_type type;
	
	// possible data about the token
	// might be a constant expression number
	// might not be used
	uint64_t data;
	
	// possible string of characters
	// used to store possible symbol names
	char* symbol;
	
} Token;

// list of tokens
typedef struct {
	
	// number of tokens
	size_t size;
	
	// actual list of tokens
	Token* tokens;
	
} Token_list;

// convert source code to a list of tokens
Token_list create_token_list(char* source_code);

// destruct a Token_list (mainly free Token* inside struct)
void destruct_token_list(Token_list* token_list);
