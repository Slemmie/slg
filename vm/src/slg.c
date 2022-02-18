// main C file, implementing entry point of
// - compiler option
// - linker option
// - runner (VM) option

// for now, we are building for linux only
#ifndef __linux__
#error "unsupported OS"
#endif

#include "util/exit_codes.h"
#include "check_argv.h"
#include "print_help.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	// run list of args through a simple error checking procedure
	// should catch most cases of incorrect syntax
	// this also sets neccesary information needed to decide modes and input for modules
	if (check_argv_errors(argc - 1, &argv[1])) {
		// error(s) were found, halt
		// the function has already printed potential error messages
		return SLG_EXIT_BAD_ARGV;
	}
	
	// if help section is wanted, print it, then exit
	if (slg_mode == SLG_MODE_HELP) {
		pr_help_argv();
		return SLG_EXIT_SUCCESSFUL;
	}
	
	// if command-line information wasn't set properly, then exit
	if (slg_mode == SLG_MODE_NONE ||
	(slg_mode != SLG_MODE_RUN && output_file_path == NULL) ||
	input_file_paths == NULL) {
		printf("[fatal error]: unknown command-line interpreting error\n");
		return SLG_EXIT_BAD_ARGV;
	}
	
	// launch modules here...
	
	// free input_file_paths
	if (input_file_paths) {
		free(input_file_paths);
	}
	
	return SLG_EXIT_SUCCESSFUL;
}
