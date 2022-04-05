// parse command line arguments
// returns an object with the extracted information

#pragma once

#include <stddef.h>

typedef enum {
	
	ARGV_FILE_TYPE_NONE  = 0,
	ARGV_FILE_TYPE_SLG   = 1 << 0,
	ARGV_FILE_TYPE_ASM   = 1 << 1,
	ARGV_FILE_TYPE_OBJ   = 1 << 2,
	ARGV_FILE_TYPE_EXEC  = 1 << 3
	
} Argv_file_type;

typedef struct {
	
	size_t input_file_count;
	char** input_file_paths;
	char** input_file_paths_prefix;
	char** input_file_paths_suffix;
	Argv_file_type* input_file_types;
	
	char* output_file_path;
	char* output_file_path_prefix;
	char* output_file_path_suffix;
	Argv_file_type output_file_type;
	
} Argv_info;

void parse_argv(Argv_info* argv_info, int argc, char** argv);

void destruct_argv_info(Argv_info* argv_info);
