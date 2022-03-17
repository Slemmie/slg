// implementation of the linker

#include "../util/exit_codes.h"

#include "read_binaries.h"
#include "symbol.h"
#include "make_executable.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int link_binaries(const char* output_file, const char** input_files, size_t input_count) {
	// first aquire the input binaries
	// first sizeof(uint64_t) bytes hold the file size
	void** input_binaries = read_binaries(input_files, input_count);
	
	// check if something went wrong
	if (!input_binaries) {
		printf("[fatal error]: failed to read input file(s)\n");
		exit(SLG_EXIT_FILE_ERROR);
	}
	
	// create a list of symbols
	// only create one when we encounter a definition
	Symbol_list symbol_list = create_symbol_list(input_binaries, input_count);
	
	// now make the actual file
	// put all the binaries in succession
	// remove all the label definition strings and set the appropriate instruction pointer in the symbol list
	// also, for all the other mentions of any symbol, set a unique index in an array
	// with a pointer to the symbol that it wants to point to in the end
	// then change the string to a 64 bit number 0 and update the number in the end
	// that way, all offsets are the same as they will be in the end
	size_t result_length;
	uint8_t* final_buffer = make_executable(&symbol_list, input_binaries, input_count, &result_length);
	
	// write the buffer to the output file
	FILE* outfile = fopen(output_file, "wb");
	if (!outfile) {
		printf("[fatal error]: failed to open file '%s'\n", output_file);
		exit(SLG_EXIT_FILE_ERROR);
	}
	fwrite(final_buffer, sizeof(uint8_t), result_length, outfile);
	fclose(outfile);
	
	// free the symbol list
	destruct_symbol_list(&symbol_list);
	
	// free the input binaries
	for (size_t i = 0; i < input_count; i++) {
		free(input_binaries[i]);
	}
	free(input_binaries);
	
	return 0;
}
