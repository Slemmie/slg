#include "parse_command_line.h"

#include <stdlib.h>

// rules
//
// if -s or -c is specified with input files beoynd the respective states - they are ignored and warned about
// if an output file is specified, multiple input files are only allowed if the output file is an executable
// default output files are: abc.slg -> abc.asm -> abc.o -> a.out

Command_line_result construct_clr(int argc, char** argv) {
	Command_line_result clr;
	
	clr.clo = 0;
	clr.count_input_files = 0;
	clr.input_files = NULL;
	clr.output_file = NULL;
	clr.count_output_files = 0;
	clr.output_files = NULL;
	
	// ...
	
	return clr;
}

void destruct_clr(Command_line_result* clr) {
	if (clr->input_files) {
		for (size_t i = 0; i < clr->count_input_files; i++) {
			if (clr->input_files[i]) {
				free(clr->input_files[i]);
			}
		}
	}
	
	if (clr->output_file) {
		free(clr->output_file);
	}
	
	if (clr->output_files) {
		for (size_t i = 0; i < clr->count_output_files; i++) {
			if (clr->output_files[i]) {
				free(clr->output_files[i]);
			}
		}
	}
}
