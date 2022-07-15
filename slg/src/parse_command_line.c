#include "parse_command_line.h"

#include <stdlib.h>

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
