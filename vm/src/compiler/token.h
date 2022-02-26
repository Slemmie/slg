// source file gets broken into a sequence of tokens

#pragma once

#include <stdint.h>

// all supported types of tokens
typedef enum {
	
	TOK_NONE = 0,
	
	// grow the stack by one byte
	TOK_GROW = 1,
	
	// move a byte (constant expression number or stack pointer) into somewhere in the stack
	TOK_MOVE = 2,
	// move 4 bytes (constant expression number or stack pointer) into somewhere in the stack
	TOK_MOVE4 = 3,
	
	// jump to a label
	TOK_JUMP = 4,
	// jump to a label if arg1 == arg2
	TOK_JUMP_EQUAL = 5,
	// jump to a label if arg1 != arg2
	TOK_JUMP_NEQUAL = 6,
	// jump to a label if arg1 < arg2
	TOK_JUMP_LESS = 7,
	
	// add 4 bytes (stack pointer contents) to somewhere in stack
	TOK_ADD = 8,
	// subtract 4 bytes (stack pointer contents) from somewhere in stack
	TOK_SUB = 9,
	// multiply 4 bytes (stack pointer contents) to somwhere in stack
	TOK_MUL = 10,
	// divide somewhere in stack by 4 bytes (stack pointer contents)
	TOK_DIV = 11,
	
	// call system call write on a single byte (stack pointer contents)
	// will be converted to whatever char is in ascii table of passed value
	TOK_SYS_WRITE = 12,
	
	// call system call read on a single character (byte)
	// put result of ascii value of read character into somewhere in stack
	TOK_SYS_READ = 13,
	
	// number of fields (not an operation)
	TOK_CNT = 14
	
} Token_type;

// actual token
typedef struct {
	
	Token_type type;
	
	// possible data about the token
	// might be a constant expression number
	// might not be used
	unsigned long long data;
	
} Token;

// list of tokens
typedef struct {
	
	// number of tokens
	size_t size;
	
	// actual list of tokens
	Token* tokens;
	
} Token_list;
