#pragma once

#include <stddef.h>

typedef enum {
	
	CLO_NONE = 0,
	
	CLO_S = 1 << 0, // compile each input file and give assembly file(s) as output(s)
	CLO_C = 1 << 1, // compile and assemble each file and give .o file(s) as output(s)
	CLO_O = 1 << 2, // if a single output file is desired, optional naming of the file here
	CLO_E = 1 << 3, // bit is set if an executable is expected
	
} Command_line_option;

typedef enum {
	
	FF_NONE = 0,
	
	FF_SLG = 1 << 0, // slg source code format
	FF_ASM = 1 << 1, // assembly format
	FF_OBJ = 1 << 2, // object file format
	FF_EXE = 1 << 3, // executable file format
	
} File_format;

typedef struct {
	
	// mask of options, query it to know for instance if a single or multiple output files
	Command_line_option clo;
	
	// list of input filepaths
	size_t count_input_files;
	char** input_files;
	char** input_file_no_ext; // input file name without extension
	// list specifying state (type) of input files, parwise matched with input file indices
	File_format* input_files_format;
	
	// exactly one of the following should not be NULL
	// name of single output file (if used)
	char* output_file;
	// names of output files, parwise matched with input file indices (if used)
	char** output_files;
	
} Command_line_result;

Command_line_result construct_clr(int argc, char** argv);

void destruct_clr(Command_line_result* clr);
