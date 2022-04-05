// implements parse_argv.h

#include "parse_argv.h"

#include "tmp_dir_manager.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

void parse_argv(Argv_info* argv_info, int argc, char** argv) {
	Argv_info* result = argv_info;
	*result = (Argv_info) {
		0, NULL, NULL, NULL, 0, NULL, NULL, NULL, 0
	};
	
	int has_s_c_flag = 0;
	int has_o_flag = 0;
	
	// first parse
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-o")) {
			has_o_flag = 1;
			// error checking
			if (i + 1 >= argc) {
				printf("[fatal]: missing filename after '-o'\n");
				clean_exit(1);
			}
			if (result->output_file_path) {
				printf("[fatal]: multiple output files specified\n");
				clean_exit(1);
			}
			// set output_file_path
			result->output_file_path = malloc(sizeof(char) * (strlen(argv[++i]) + 1));
			memcpy(result->output_file_path, argv[i], sizeof(char) * strlen(argv[i]));
			result->output_file_path[strlen(argv[i])] = '\0';
			// find last '.' character of file path
			int dot_index = -1;
			for (int j = 0; argv[i][j] != '\0'; j++) {
				if (argv[i][j] == '.') {
					dot_index = j;
				}
			}
			// set output_file_path_prefix
			result->output_file_path_prefix =
			malloc(sizeof(char) * (dot_index == -1 ? strlen(argv[i]) + 1 : dot_index + 1));
			for (int j = 0; j != dot_index && j < strlen(argv[i]); j++) {
				result->output_file_path_prefix[j] = argv[i][j];
			}
			result->output_file_path_prefix[dot_index == -1 ? strlen(argv[i]) : dot_index] = '\0';
			// set output_file_path_suffix
			result->output_file_path_suffix =
			malloc(sizeof(char) * (strlen(argv[i]) - strlen(result->output_file_path_prefix) + 1));
			for (int j = strlen(result->output_file_path_prefix), l = 0; j < strlen(argv[i]); j++, l++) {
				result->output_file_path_suffix[l] = argv[i][j];
			}
			result->output_file_path_suffix
			[strlen(argv[i]) - strlen(result->output_file_path_prefix)] = '\0';
			// set output_file_type if it has not been set already (do not override -c/-s flags)
			if (result->output_file_type == ARGV_FILE_TYPE_NONE) {
				if (!strcmp(result->output_file_path_suffix, ".asm")) {
					result->output_file_type = ARGV_FILE_TYPE_ASM;
				} else if (!strcmp(result->output_file_path_suffix, ".o")) {
					result->output_file_type = ARGV_FILE_TYPE_OBJ;
				} else {
					result->output_file_type = ARGV_FILE_TYPE_EXEC;
				}
			}
		} else if (!strcmp(argv[i], "-c")) {
			if (has_s_c_flag) {
				printf("[fatal]: found multiple '-s'/'-c' flags in command line\n");
				clean_exit(1);
			}
			has_s_c_flag = 1;
			result->output_file_type = ARGV_FILE_TYPE_OBJ;
		} else if (!strcmp(argv[i], "-s")) {
			if (has_s_c_flag) {
				printf("[fatal]: found multiple '-s'/'-c' flags in command line\n");
				clean_exit(1);
			}
			has_s_c_flag = 1;
			result->output_file_type = ARGV_FILE_TYPE_ASM;
		} else {
			result->input_file_count++;
		}
	}
	
	// second parse - fill input files arrays
	result->input_file_paths = malloc(sizeof(char*) * result->input_file_count);
	result->input_file_paths_prefix = malloc(sizeof(char*) * result->input_file_count);
	result->input_file_paths_suffix = malloc(sizeof(char*) * result->input_file_count);
	result->input_file_types = malloc(sizeof(Argv_file_type) * result->input_file_count);
	for (int i = 1, j = 0; i < argc; i++) {
		// ignore flags
		if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "-c")) {
			continue;
		}
		// ignore flag and following output file path
		if (!strcmp(argv[i], "-o")) {
			i++;
			continue;
		}
		// this is an input file
		// set input_file_paths[j]
		result->input_file_paths[j] = malloc(sizeof(char) * (strlen(argv[i]) + 1));
		memcpy(result->input_file_paths[j], argv[i], sizeof(char) * strlen(argv[i]));
		result->input_file_paths[j][strlen(argv[i])] = '\0';
		// find last '.' character of file path
		int dot_index = -1;
		for (int k = 0; argv[i][k] != '\0'; k++) {
			if (argv[i][k] == '.') {
				dot_index = k;
			}
		}
		// set input_file_paths_prefix[j]
		result->input_file_paths_prefix[j] =
		malloc(sizeof(char) * (dot_index == -1 ? strlen(argv[i]) + 1 : dot_index + 1));
		for (int k = 0; k != dot_index && k < strlen(argv[i]); k++) {
			result->input_file_paths_prefix[j][k] = argv[i][k];
		}
		result->input_file_paths_prefix[j][dot_index == -1 ? strlen(argv[i]) : dot_index] = '\0';
		// set input_file_paths_suffix[j]
		result->input_file_paths_suffix[j] =
		malloc(sizeof(char) * (strlen(argv[i]) - strlen(result->input_file_paths_prefix[j]) + 1));
		for (int k = strlen(result->input_file_paths_prefix[j]), l = 0; k < strlen(argv[i]); k++, l++) {
			result->input_file_paths_suffix[j][l] = argv[i][k];
		}
		result->input_file_paths_suffix[j]
		[strlen(argv[i]) - strlen(result->input_file_paths_prefix[j])] = '\0';
		// set input_file_types[j]
		if (!strcmp(result->input_file_paths_suffix[j], ".asm")) {
			result->input_file_types[j] = ARGV_FILE_TYPE_ASM;
		} else if (!strcmp(result->input_file_paths_suffix[j], ".o")) {
			result->input_file_types[j] = ARGV_FILE_TYPE_OBJ;
		} else {
			result->input_file_types[j] = ARGV_FILE_TYPE_SLG;
		}
		// next index is j + 1
		j++;
	}
	
	// check for input file count and input/output file type matching
	if (!result->input_file_count) {
		printf("[fatal]: no input file provided\n");
		clean_exit(1);
	}
	if (result->input_file_count > 1 && has_o_flag && has_s_c_flag) {
		printf("[fatal]: cannot specify '-o' with '-s'/'-c'\n");
		clean_exit(1);
	}
	if (result->input_file_count > 1 && (
	result->output_file_type == ARGV_FILE_TYPE_ASM ||
	result->output_file_type == ARGV_FILE_TYPE_OBJ)) {
		printf("[fatal]: cannot specify multiple input files with '.asm'/'.o' output file\n");
		clean_exit(1);
	}
	
	// if no output file is set, set a default
	if (!result->output_file_path) {
		switch (result->output_file_type) {
			case ARGV_FILE_TYPE_ASM: {
				// set output_file_path
				result->output_file_path =
				malloc(sizeof(char) * (strlen(result->input_file_paths_prefix[0]) + 5));
				memcpy(result->output_file_path, result->input_file_paths_prefix,
				sizeof(char) * strlen(result->input_file_paths_prefix[0]));
				strcpy(result->output_file_path + strlen(result->input_file_paths_prefix[0]), ".asm");
				// set output_file_path_prefix
				result->output_file_path_prefix =
				malloc(sizeof(char) * (strlen(result->input_file_paths_prefix[0]) + 1));
				memcpy(result->output_file_path_prefix, result->input_file_paths_prefix[0],
				sizeof(char) * strlen(result->input_file_paths_prefix[0]));
				// set output_file_path_suffix
				result->output_file_path_suffix = malloc(sizeof(char) * 5);
				strcpy(result->output_file_path_suffix, ".asm");
				break;
			}
			case ARGV_FILE_TYPE_OBJ: {
				// set output_file_path
				result->output_file_path =
				malloc(sizeof(char) * (strlen(result->input_file_paths_prefix[0]) + 3));
				memcpy(result->output_file_path, result->input_file_paths_prefix,
				sizeof(char) * strlen(result->input_file_paths_prefix[0]));
				strcpy(result->output_file_path + strlen(result->input_file_paths_prefix[0]), ".o");
				// set output_file_path_prefix
				result->output_file_path_prefix =
				malloc(sizeof(char) * (strlen(result->input_file_paths_prefix[0]) + 1));
				memcpy(result->output_file_path_prefix, result->input_file_paths_prefix[0],
				sizeof(char) * strlen(result->input_file_paths_prefix[0]));
				// set output_file_path_suffix
				result->output_file_path_suffix = malloc(sizeof(char) * 3);
				strcpy(result->output_file_path_suffix, ".o");
				break;
			}
			default:
			case ARGV_FILE_TYPE_NONE:
			case ARGV_FILE_TYPE_EXEC: {
				result->output_file_path = malloc(sizeof(char) * 6);
				strcpy(result->output_file_path, "a.out");
				break;
			}
		};
	}
}

void destruct_argv_info(Argv_info* argv_info) {
	if (argv_info->input_file_paths) {
		for (size_t i = 0; i < argv_info->input_file_count; i++) {
			free(argv_info->input_file_paths[i]);
			argv_info->input_file_paths[i] = NULL;
		}
		free(argv_info->input_file_paths);
		argv_info->input_file_paths = NULL;
	}
	if (argv_info->input_file_paths_prefix) {
		for (size_t i = 0; i < argv_info->input_file_count; i++) {
			free(argv_info->input_file_paths_prefix[i]);
			argv_info->input_file_paths_prefix[i] = NULL;
		}
		free(argv_info->input_file_paths_prefix);
		argv_info->input_file_paths_prefix = NULL;
	}
	if (argv_info->input_file_paths_suffix) {
		for (size_t i = 0; i < argv_info->input_file_count; i++) {
			free(argv_info->input_file_paths_suffix[i]);
			argv_info->input_file_paths_suffix[i] = NULL;
		}
		free(argv_info->input_file_paths_suffix);
		argv_info->input_file_paths_suffix = NULL;
	}
	if (argv_info->input_file_types) {
		free(argv_info->input_file_types);
		argv_info->input_file_types = NULL;
	}
	if (argv_info->output_file_path) {
		free(argv_info->output_file_path);
		argv_info->output_file_path = NULL;
	}
	if (argv_info->output_file_path_prefix) {
		free(argv_info->output_file_path_prefix);
		argv_info->output_file_path_prefix = NULL;
	}
	if (argv_info->output_file_path_suffix) {
		free(argv_info->output_file_path_suffix);
		argv_info->output_file_path_suffix = NULL;
	}
}
