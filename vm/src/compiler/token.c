// implementation of token.h stuff

#include "token.h"

#include "../util/exit_codes.h"

#include <stdlib.h>
#include <stdio.h>

// utility function for checking whether a character is a whitespace
int is_whitespace(char character) {
	return
	character == ' ' ||
	character == '\t' ||
	character == '\n' ||
	character == '\v' ||
	character == '\f' ||
	character == '\r' ||
	character == '\0';
}

// utility function for checking whether a character is a digit
int is_digit(char character) {
	return character >= '0' && character <= '9';
}

// create a token from a snippet of source code
Token create_token(char* it, size_t size) {
	// this should not happen
	// if it does, it should not be because of a user mistake
	if (!size) {
		printf("[fatal error]: unexpected source code interpretation error\n");
		exit(SLG_EXIT_SOURCE_CODE_ERROR);
	}
	
	Token result;
	result.type = TOK_NONE;
	
	/// TOK_NUMBER ///
	// if the first character is a digit or a '-' (minus sign),
	// assume we are trying to type a constant expression value
	if (is_digit(*it) || *it == '-') {
		// if size == 1 and *it == '-', there is no actual number
		// for now, a stand-alone '-' does not mean anything, so just throw an error
		if (size == 1 && *it == '-') {
			printf("[fatal error]: unexpected stand-alone '-' character\n");
			exit(SLG_EXIT_SOURCE_CODE_ERROR);
		}
		
		// check whether all characters are indeed digits
		for (size_t i = 0; i < size; i++) {
			if (!is_digit(it + size)) {
				printf("[fatal error]: unexpected non-digit character in numerical constant expression\n");
				exit(SLG_EXIT_SOURCE_CODE_ERROR);
			}
		}
		
		// convert to integer
		// only accept base 10 numbers for now
		// we are not checking for any '0x' prefix or the like
		result.data = strtol(it, it + size, 10);
		
		// return result
		result.type = TOK_NUMBER;
		return result;
	}
	
	// check for any keywords
	// if we do not find a match, then for now we throw an error
	
	/// TOK_GROW ///
	if (!strcmp("grow", it)) {
		result.type = TOK_GROW;
		return result;
	}
	
	/// TOK_MOVE ///
	if (!strcmp("move", it)) {
		result.type = TOK_MOVE;
		return result;
	}
	
	/// TOK_MOVE4 ///
	if (!strcmp("move4", it)) {
		result.type = TOK_MOVE4;
		return result;
	}
	
	/// TOK_JUMP ///
	if (!strcmp("jump", it)) {
		result.type = TOK_JUMP;
		return result;
	}
	
	/// TOK_JUMP_EQUAL ///
	if (!strcmp("jump_equal", it)) {
		result.type = TOK_JUMP_EQUAL;
		return result;
	}
	
	/// TOK_JUMP_NEQUAL ///
	if (!strcmp("jump_nequal", it)) {
		result.type = TOK_JUMP_NEQUAL;
		return result;
	}
	
	/// TOK_JUMP_LESS ///
	if (!strcmp("jump_less", it)) {
		result.type = TOK_JUMP_LESS;
		return result;
	}
	
	/// TOK_ADD ///
	if (!strcmp("add", it)) {
		result.type = TOK_ADD;
		return result;
	}
	
	/// TOK_SUB ///
	if (!strcmp("sub", it)) {
		result.type = TOK_SUB;
		return result;
	}
	
	/// TOK_MUL ///
	if (!strcmp("mul", it)) {
		result.type = TOK_MUL;
		return result;
	}
	
	/// TOK_DIV ///
	if (!strcmp("div", it)) {
		result.type = TOK_DIV;
		return result;
	}
	
	/// TOK_SYS_WRITE ///
	if (!strcmp("write", it)) {
		result.type = TOK_SYS_WRITE;
		return result;
	}
	
	/// TOK_SYS_READ ///
	if (!strcmp("read", it)) {
		result.type = TOK_SYS_READ;
		return result;
	}
	
	/// TOK_ADDRESS ///
	if (!strcmp("&", it)) {
		result.type = TOK_ADDRESS;
		return result;
	}
	
	// throw an error, we did not find any accepted interpretations of the number
	printf("[fatal error]: unknown symbol\n");
	exit(SLG_EXIT_SOURCE_CODE_ERROR);
	return result;
}

// convert source code to a list of tokens
Token_list create_token_list(const char* source_code) {
	// first count the number of expected tokens
	// we count number of times we encounter a
	// white-space character with a non-white-space as previous character
	size_t expected_token_count = 0;
	char previous_character = '\0';
	for (char* it = source_code; *it != '\0'; it++) {
		expected_token_count += !is_whitespace(*it) && is_whitespace(previous_character);
		previous_character = *it;
	}
	
	// use exptected size to allocate a list of empty tokens
	Token_list result;
	result.size = expected_token_count;
	result.tokens = malloc(sizeof(Token) * expected_token_count);
	
	// now fill out the contents of each token
	for (char* it = source_code; *it != '\0'; it++) {
		// continue in case of multiple whitespaces in a row
		if (is_whitespace(*it)) {
			continue;
		}
		
		// count the number of characters in the token
		char* begin = it;
		size_t character_count = 0;
		for (; !is_whitespace(*it); it++) {
			character_count++;
		}
		// use buffer to create actual token information
		// temporarily set the whitespace character after the characters to '\0'
		char temp = *it;
		*it = '\0';
		result.tokens[current_token_count++] = create_token(begin, (size_t) (it - begin));
		*it = temp;
		// we are not pointing to a whitespace...
	}
	
	return result;
}
