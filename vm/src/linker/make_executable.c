// make the final executable

#include "make_executable.h"

#include "symbol_list.h"

#include <stdlib.h>

uint8_t* make_executable(Symbol_list* symbol_list, void** binaries, size_t input_count, size_t* result_length) {
	// first count the number of symbol mentions outside of defintions
	size_t symbol_mentions = 0;
	
	// allocate array for holding indices of symbols wanted by symbol mentions
	
	// allocate result array
	
	// generate the buffer on the fly, filling in everything except instr pointers for the symbol mentions
	
	// fill out instruction pointers for the symbol mentions
	
	// done!
	return ...;
}
