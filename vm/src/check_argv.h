// check for errors in command-line arguments passed to main()

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

// modes
#define SLG_MODE_NONE         0
#define SLG_MODE_RUN          1
#define SLG_MODE_COMPILE      2
#define SLG_MODE_LINK         3
#define SLG_MODE_COMPILE_LINK 4

// module input
int slg_mode = SLG_MODE_NONE;
char* output_file_path = NULL;
int input_file_paths_count = 0;
char** input_file_paths = NULL;

// returns 0 if no erros are found
// prints potential error messages to stdout
// also populates neccesary information about modes/input-files/output-files
int check_argv_errors(int argc, char** argv) {
	int run_flag_id = ~0;
	int o_flag_id = ~0;
	int file_name_count = 0;
	
	int* is_file_name = malloc(sizeof(int) * argc);
	memset(is_file_name, 0, sizeof(int) * argc);
	
	for (int i = 0; i < argc; i++) {
		if (!strcmp("-r", argv[i])) {
			// multiple -r flags found
			if (run_flag_id != ~0) {
				printf("[fatal error]: multiple occurrences of '-r' flag found\n");
				free(is_file_name);
				return 1;
			}
			
			run_flag_id = i;
		} else if (!strcmp("-o", argv[i])) {
			// multiple -o flags found
			if (o_flag_id != ~0) {
				printf("[fatal error]: multiple occurrences of '-o' flag found\n");
				free(is_file_name);
				return 1;
			}
			
			o_flag_id = i;
		} else {
			// default to interpreting the argument as a file name
			file_name_count++;
			is_file_name[i] = 1;
		}
	}
	
	// if there are zero file names passed, then we for sure don't have any input nor output files
	if (!file_name_count) {
		printf("[fatal error]: no input/output files found\n");
		free(is_file_name);
		return 1;
	}
	
	// run flag set (-r), we should attempt to use runner module
	if (run_flag_id != ~0) {
		// there should be exactly 2 arguments (-r flag and path to executable)
		if (argc != 2) {
			printf("[fatal error]: bad number of arguments for run mode\n");
			free(is_file_name);
			return 1;
		}
		
		char* exec_path = run_flag_id == 0 ? argv[1] : argv[0];
		
		// check if executable file exists
		// using system call access(...)
		if (access(exec_path, F_OK) != 0) {
			printf("[fatal error]: executable '%s' doesn't exist\n", exec_path);
			free(is_file_name);
			return 1;
		}
		
		// everything ok for run mode
		
		slg_mode = SLG_MODE_RUN;
		
		free(is_file_name);
		return 0;
	}
	
	// non-run mode
	
	output_file_path = o_flag_id + 1 == argc || o_flag_id == ~0 ? NULL : argv[o_flag_id + 1];
	
	// specific output file name requested
	if (o_flag_id != ~0) {
		// '-o' flag is the last argument provided, so we are missing the requested output file name
		// or
		// following argument is a flag, so we are missing the requested output file name
		if (o_flag_id + 1 == argc || output_file_path[0] == '-') {
			printf("[fatal error]: missing output file name\n");
			free(is_file_name);
			return 1;
		}
		
		// check if output file name is the same as one of the input files names
		for (int i = 0; i < argc; i++) {
			if (i == o_flag_id + 1) {
				continue;
			}
			
			if (!strcmp(argv[i], output_file_path)) {
				printf("[fatal error]: output file name is equal to an input file name\n");
				free(is_file_name);
				return 1;
			}
		}
	}
	
	// if output file name has '.o' extension, we expect exactly one input file
	if (output_file_path && strlen(output_file_path) >= 2 &&
	!strcmp(&output_file_path[strlen(output_file_path) - 2], ".o")) {
		// should be 2, one input file and one output file
		if (file_name_count != 2) {
			printf(
			"[fatal error]: expected exactly one input file when creating a '.o' file, found %d\n",
			file_name_count - 1);
			free(is_file_name);
			return 1;
		}
		
		// exactly one input file has been passed, check if it exists
		// using system call access(...)
		for (int i = 0; i < argc; i++) {
			if (is_file_name[i] && strcmp(output_file_path, argv[i])) {
				if (access(argv[i], F_OK) != 0) {
					printf("[fatal error]: input file '%s' doesn't exist\n", argv[i]);
					free(is_file_name);
					return 1;
				}
			}
		}
		
		// everything ok for creating a '.o' file
		
		slg_mode = SLG_MODE_COMPILE;
		input_file_paths = malloc(sizeof(char*) * 1);
		input_file_paths[0] = argv[0];
		input_file_paths_count = 1;
		
		free(is_file_name);
		return 0;
	}
	
	// we are either linking a bunch of .o files
	// or directly compiliing+linking one or more source code files
	
	// check the number of '.o' input files,
	// should be equal to 0 or file_name_count - output_file_exists
	int dot_o_files_passed = 0;
	for (int i = 0; i < argc; i++) {
		if (strlen(argv[i]) >= 2 && !strcmp(&argv[i][strlen(argv[i]) - 2], ".o")) {
			dot_o_files_passed++;
		}
	}
	if (dot_o_files_passed != 0 && dot_o_files_passed != file_name_count - (o_flag_id != ~0)) {
		printf("[fatal error]: '.o' input file extensions and non-'.o' input file extensions cannot be mixed\n");
		free(is_file_name);
		return 1;
	}
	
	// check that all input files exist
	// using system call access(...)
	
	// we also populate input_file_paths
	int infile_arr_ptr = 0;
	input_file_paths_count = file_name_count - (o_flag_id != ~0);
	input_file_paths = malloc(sizeof(char*) * input_file_paths_count);
	
	for (int i = 0; i < argc; i++) {
		// skip output file
		if (output_file_path && !strcmp(argv[i], output_file_path)) {
			continue;
		}
		
		if (is_file_name[i]) {
			input_file_paths[infile_arr_ptr++] = argv[i];
			if (access(argv[i], F_OK) != 0) {
				free(input_file_paths);
				input_file_paths = NULL;
				printf("[fatal error]: input file '%s' doesn't exist\n", argv[i]);
				free(is_file_name);
				return 1;
			}
		}
	}
	
	// check if there are no input files
	if (file_name_count - (o_flag_id != ~0) == 0) {
		printf("[fatal error]: no input files found\n");
		free(is_file_name);
		return 1;
	}
	
	// everything ok
	
	// if there are no '.o' files      -> compile source code files then link
	// else, there are only '.o' files -> simply link the '.o' files
	if (dot_o_files_passed == 0) {
		slg_mode = SLG_MODE_COMPILE_LINK;
	} else {
		slg_mode = SLG_MODE_LINK;
	}
	
	// if output file has not been explicitly set by '-o' flag, then set default name
	if (output_file_path == NULL) {
		output_file_path = "a.out";
	}
	
	free(is_file_name);
	return 0;
}
