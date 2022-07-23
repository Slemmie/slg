// implements parse_command_line.h

#include "parse_command_line.h"

#include "error.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

char* _get_extension(char* str);

// rules
//
// if both -s and -c is specified, default to handling the input as if only -c is specified
// if -s or -c is specified with input files beoynd the respective states - they are ignored and warned about
// if an output file is specified, multiple input files are only allowed if the output file is an executable
// default output files are: abc.slg -> abc.asm -> abc.o -> a.out

Command_line_result construct_clr(int argc, char** argv) {
	Command_line_result clr;
	
	clr.clo = 0;
	clr.count_input_files = 0;
	clr.input_files = NULL;
	clr.input_file_no_ext = NULL;
	clr.input_files_format = NULL;
	clr.output_file = NULL;
	clr.output_files = NULL;
	
	// keep track of which command line tokens have been dealt with
	int* dealt_with = malloc(sizeof(int) * argc);
	if (!dealt_with) {
		internal_fatal_error("malloc failed");
	}
	memset(dealt_with, 0, sizeof(int) * argc);
	
	if (!dealt_with) {
		internal_fatal_error("malloc failed");
	}
	
	// check if an output filepath is specified
	for (int i = 1; i < argc; i++) {
		if (!strcmp("-o", argv[i])) {
			if (i + 1 == argc) {
				free(dealt_with);
				destruct_clr(&clr);
				fatal_error("missing output file after '-o' command line token");
			}
			
			clr.clo |= CLO_O;
			
			dealt_with[i] = dealt_with[i + 1] = 1;
			
			size_t len = strlen(argv[++i]);
			clr.output_file = malloc(sizeof(char) * (len + 1));
			
			if (!clr.output_file) {
				free(dealt_with);
				destruct_clr(&clr);
				internal_fatal_error("malloc failed");
			}
			
			memcpy(clr.output_file, argv[i], len);
			clr.output_file[len] = '\0';
			
			break;
		}
	}
	
	// determine whether -s or -c flags have been provided
	int s_flag = 0;
	int c_flag = 0;
	
	for (int i = 1; i < argc; i++) {
		if (dealt_with[i]) {
			continue;
		}
		
		if (!strcmp("-s", argv[i])) {
			s_flag = 1;
			dealt_with[i] = 1;
		}
		
		if (!strcmp("-c", argv[i])) {
			c_flag = 1;
			dealt_with[i] = 1;
		}
	}
	
	if (s_flag && c_flag) {
		s_flag = 0;
	}
	
	if (s_flag) {
		clr.clo |= CLO_S;
	}
	if (c_flag) {
		clr.clo |= CLO_C;
	}
	
	// if an executable is expected, but no output file was specified, set a.out by default
	if (!s_flag && !c_flag && !(clr.clo & CLO_O)) {
		assert(!clr.output_file);
		
		clr.clo |= CLO_O;
		
		const size_t len = 5;
		clr.output_file = malloc(sizeof(char) * (len + 1));
		
		if (!clr.output_file) {
			free(dealt_with);
			destruct_clr(&clr);
			internal_fatal_error("malloc failed");
		}
		
		memcpy(clr.output_file, "a.out", len);
		clr.output_file[len] = '\0';
	}
	
	// if an executable is expected, set appropriate bit
	if (!s_flag && !c_flag) {
		clr.clo |= CLO_E;
	}
	
	// check for input files that are beyond the potential -s/-c states
	// otherwise add them to the array of input files
	for (int i = 1; i < argc; i++) {
		if (dealt_with[i]) {
			continue;
		}
		
		clr.count_input_files++;
	}
	
	clr.input_files = malloc(sizeof(char*) * clr.count_input_files);
	clr.input_file_no_ext = malloc(sizeof(char*) * clr.count_input_files);
	clr.input_files_format = malloc(sizeof(File_format) * clr.count_input_files);
	if (!(clr.clo & CLO_E)) {
		clr.output_files = malloc(sizeof(char*) * clr.count_input_files);
	}
	
	{
		size_t input_file_ptr = 0;
		for (int i = 1; i < argc; i++) {
			if (dealt_with[i]) {
				continue;
			}
			
			dealt_with[i] = 1;
			
			// set filepath
			size_t len = strlen(argv[i]);
			clr.input_files[input_file_ptr] = malloc(sizeof(char) * (len + 1));
			
			if (!clr.input_files[input_file_ptr]) {
				free(dealt_with);
				destruct_clr(&clr);
				internal_fatal_error("malloc failed");
			}
			
			memcpy(clr.input_files[input_file_ptr], argv[i], len);
			clr.input_files[input_file_ptr][len] = '\0';
			
			// get extension
			char* ext = _get_extension(argv[i]);
			assert(ext);
			
			// set extensionless filepath
			len = strlen(argv[i]) - strlen(ext);
			clr.input_file_no_ext[input_file_ptr] = malloc(sizeof(char) * (len + 1));
			
			if (!clr.input_file_no_ext[input_file_ptr]) {
				free(dealt_with);
				destruct_clr(&clr);
				internal_fatal_error("malloc failed");
			}
			
			memcpy(clr.input_file_no_ext[input_file_ptr], argv[i], len);
			clr.input_file_no_ext[input_file_ptr][len] = '\0';
			
			// set file format
			clr.input_files_format[input_file_ptr] = FF_SLG;
			if (!strcmp(ext, ".asm")) {
				clr.input_files_format[input_file_ptr] = FF_ASM;
			}
			if (!strcmp(ext, ".o")) {
				clr.input_files_format[input_file_ptr] = FF_OBJ;
			}
			
			// if an executable is not expected, set output file path matching the input file path
			if (!(clr.clo & CLO_E)) {
				len = strlen(clr.input_file_no_ext[input_file_ptr]);
				if (clr.clo & CLO_S) {
					len += 4;
				} else if (clr.clo & CLO_C) {
					len += 2;
				} else {
					free(dealt_with);
					destruct_clr(&clr);
					internal_fatal_error("unexpected error");
				}
				
				clr.output_files[input_file_ptr] = malloc(sizeof(char) + (len + 1));
				
				if (!clr.output_files[input_file_ptr]) {
					free(dealt_with);
					destruct_clr(&clr);
					internal_fatal_error("malloc failed");
				}
				
				memcpy(clr.output_files[input_file_ptr],
				clr.input_file_no_ext[input_file_ptr],
				strlen(clr.input_file_no_ext[input_file_ptr]));
				
				if (clr.clo & CLO_S) {
					clr.output_files[input_file_ptr][len - 4] = '.';
					clr.output_files[input_file_ptr][len - 3] = 'a';
					clr.output_files[input_file_ptr][len - 2] = 's';
					clr.output_files[input_file_ptr][len - 1] = 'm';
				} else if (clr.clo & CLO_C) {
					clr.output_files[input_file_ptr][len - 2] = '.';
					clr.output_files[input_file_ptr][len - 1] = 'o';
				}
				
				clr.output_files[input_file_ptr][len] = '\0';
			}
			
			// increase pointer
			input_file_ptr++;
		}
	}
	
	// check whether no input files were provided
	if (!clr.count_input_files) {
		free(dealt_with);
		destruct_clr(&clr);
		fatal_error("no input file provided");
	}
	
	// check whether all input file(s) exist
	// and check for read permission for each file
	for (size_t i = 0; i < clr.count_input_files; i++) {
		if (access(clr.input_files[i], F_OK)) {
			free(dealt_with);
			destruct_clr(&clr);
			fatal_error("input file '%s' does not exist",  clr.input_files[i]);
		}
		
		if (access(clr.input_files[i], R_OK)) {
			free(dealt_with);
			destruct_clr(&clr);
			fatal_error("cannot access input file '%s' for reading", clr.input_files[i]);
		}
	}
	
	free(dealt_with);
	
	return clr;
}

void destruct_clr(Command_line_result* clr) {
	if (clr->input_files) {
		for (size_t i = 0; i < clr->count_input_files; i++) {
			if (clr->input_files[i]) {
				free(clr->input_files[i]);
			}
		}
		
		free(clr->input_files);
	}
	
	if (clr->input_files) {
		for (size_t i = 0; i < clr->count_input_files; i++) {
			if (clr->input_file_no_ext[i]) {
				free(clr->input_file_no_ext[i]);
			}
		}
		
		free(clr->input_file_no_ext);
	}
	
	if (clr->input_files_format) {
		free(clr->input_files_format);
	}
	
	if (clr->output_file) {
		free(clr->output_file);
	}
	
	if (clr->output_files) {
		for (size_t i = 0; i < clr->count_input_files; i++) {
			if (clr->output_files[i]) {
				free(clr->output_files[i]);
			}
		}
		
		free(clr->output_files);
	}
}

char* _get_extension(char* str) {
	size_t len = strlen(str);
	size_t res = len;
	
	for (size_t i = 0; i < len; i++) {
		if (str[i] == '.') {
			res = i;
		}
	}
	
	return str + res;
}
