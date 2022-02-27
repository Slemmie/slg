// implementation of the linker

#include "../util/exit_codes.h"

#include <stdio.h>
#include <stddef.h>

int link(const char* output_file, const char** input_files, size_t input_count) {
	// first aquire the input binaries
	// first sizeof(uint64_t) bytes hold the file size
	void** input_binaries = read_binaries(input_files, input_count);
	
	// check if something went wrong
	if (!input_binaries) {
		printf("[fatal error]: failed to read input file(s)\n");
		exit(SLG_EXIT_FILE_ERROR);
	}
	
	// free the input binaries
	for (size_t i = 0; i < input_count; i++) {
		free(input_binaries[i]);
	}
	free(input_binaries);
	
	return 0;
}
