// parse command line arguments
// returns an object with the extracted information

#pragma once

#include <stddef.h>

typedef enum {
	
	ARGV_FILE_TYPE_NONE  = 0,
	ARGV_FILE_TYPE_INPUT = 1 << 0,
	ARGV_FILE_TYPE_ASM   = 1 << 1,
	ARGV_FILE_TYPE_OBJ   = 1 << 2,
	ARGV_FILE_TYPE_EXEC  = 1 << 3
	
} Argv_file_type;

// all pointers are pointing to somewhere in 'char** argv' - does not need explicit destructing
typedef struct {
	
	size_t input_file_count;
	char** input_file_paths;
	Argv_file_type* input_file_types;
	
	char* output_file_path;
	Argv_file_type output_file_type;
	
} Argv_info;

Argv_info parse_argv(int argc, char** argv);
