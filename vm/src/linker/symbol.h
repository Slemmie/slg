// contains symbol and symbol list structs

#pragma once

#include <stddef.h>

typedef struct {
	
	// length of string name of the symbol
	size_t length;
	
	// the actual name
	char* name;
	
	// instruction pointer, gets assigned down the line
	size_t ip;
	
} Symbol;

typedef struct {
	
	// the number of symbols in the list
	size_t size;
	
	Symbol* symbols;
	
	// keep track of the index of the start function (the global entry)
	size_t start_function;
	
} Symbol_list;

// create a list of symbols from a series of binaries
Symbol_list create_symbol_list(void** binaries, size_t count);

// destruct a list of symbols
// mainly needed for freeing the internel Symbol* member
void destruct_symbol_list(Symbol_list* symbol_list);
