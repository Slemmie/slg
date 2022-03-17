// imeplement null_incr_binary_ptr.h

#include "null_incr_binary_ptr.h"

#include <stdint.h>

void null_incr_binary_ptr(const void* binary, size_t* ptr) {
	// switch on all possible tokens, and increment accordingly
	switch ((Token_type) (((uint8_t*) binary) + *ptr)) {
		case TOK_NONE        : (*ptr)++; break;
		case TOK_GROW        : (*ptr)++; break;
		case TOK_MOVE        : (*ptr)++; break; // the following number is a token itself
		case TOK_MOVE4       : (*ptr)++; break; // the following number is a token itself
		case TOK_JUMP        : (*ptr)++; break; // syntax is: 'jump <loc>', the location next is a TOK_NUMBER or TOK_ADDRESS
		case TOK_JUMP_EQUAL  : (*ptr)++; break; // following the 'jump_{suff} <loc>' are numbers or addresses
		case TOK_JUMP_NEQUAL : (*ptr)++; break; // -- || --
		case TOK_JUMP_LESS   : (*ptr)++; break; // -- || --
		case TOK_ADD         : (*ptr)++; break; // following this are addresses or numbers
		case TOK_SUB         : (*ptr)++; break; // -- || --
		case TOK_MUL         : (*ptr)++; break; // -- || --
		case TOK_DIV         : (*ptr)++; break; // -- || --
		case TOK_SYS_WRITE   : (*ptr)++; break; // following this is an address or a number pointing to what byte to write
		case TOK_SYS_READ    : (*ptr)++; break; // following this is an address or a number pointing to where to read to
		case TOK_NUMBER      : (*ptr) += 9; break; // add 1 for the token itself and 8 for the succeeding number
		case TOK_ADDRESS     : (*ptr)++; break; // a TOK_NUMBER always follows this
		case TOK_HALT        : (*ptr)++; break;
		case TOK_LABEL       : (*ptr)++; break; // a TOK_SYMBOL always follows this
		// 1 for the token, 8 for the string length, and the string length:
		case TOK_SYMBOL      : (*ptr) += 1 + 8 + (uint64_t) *(((uint8_t*) binary) + *ptr + 1);
		default: break;
	};
}
