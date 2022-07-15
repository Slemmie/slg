#pragma once

#include <stddef.h>

typedef enum {
	
	CLO_NONE = 0,
	
	CLO_S = 1 << 2, // compile each input file and give assembly file(s) as output(s)
	CLO_C = 1 << 0, // compile and assemble each file and give .o file(s) as output(s)
	CLO_O = 1 << 1, // if a single output file is desired, optional naming of the file here
	
} Command_line_option;

typedef struct {
	
	// mask of options, query it to know for instance if a single or multiple output files
	Command_line_option clo;
	
	// list of input filepaths
	size_t count_input_files;
	char** input_files;
	
	// exactly one of the following should not be NULL
	// name of single output file (if used)
	char* output_file;
	// names of output files, parwise matched with input file indices (if used)
	size_t count_output_files;
	char** output_files;
	
} Command_line_result;

Command_line_result construct_clr(int argc, char** argv);

void destruct_clr(Command_line_result* clr);
