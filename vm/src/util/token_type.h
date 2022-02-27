#pragma once

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
	
	// constant expression numerical value
	TOK_NUMBER = 14,
	
	// address, whenever we put '&' in source code,
	// interpret the following number as being a pointer to somewhere
	// instead of it being a raw TOK_NUMBER
	TOK_ADDRESS = 15,
	
	// halt operation, the compiler will always put a halt at the end of all the instructions
	// halt can also be called explicitly, though
	// it uses the byte stored at stack address 0 (faults if stack is empty)
	TOK_HALT = 16,
	
	// label token, used to define the decleration/definition a symbol in the source code
	// when decleration support gets added later, declerations are marked with extern kerword
	TOK_LABEL = 17,
	
	// symbol token, used for the actual symbols that the linker will deal with
	// TOK_SYMBOL appears whenever we want to jump somewhere
	TOK_SYMBOL = 18,
	
	// number of fields (not an operation)
	TOK_CNT = 19
	
} Token_type;
