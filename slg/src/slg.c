// entry point

#include "parse_command_line.h"
#include "error.h"
#include "generate_temp_file.h"
#include "file_util.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	// initialize things
	init_errors();
	
	// parse command line
	Command_line_result clr = construct_clr(argc, argv);
	
	// compile each *slg* input file
	{
		for (size_t i = 0; i < clr.count_input_files; i++) {
			if (clr.input_files_format[i] == FF_SLG) {
				char* next_file_name = generate_temp_file(clr.input_file_no_ext[i], ".asm");
				
				//slg_compile(clr.input_files[i], next_file_name);
				
				free(clr.input_files[i]);
				size_t len = strlen(next_file_name);
				clr.input_files[i] = malloc(sizeof(char) * (len + 1));
				if (!clr.input_files[i]) {
					internal_fatal_error("malloc failed");
				}
				
				memcpy(clr.input_files[i], next_file_name, len);
				clr.input_files[i][len] = '\0';
				
				free(next_file_name);
				
				clr.input_files_format[i] = FF_ASM;
			}
		}
		
		// if we are to stop at this stage...
		// copy the files from their temporary location
		if (clr.clo & CLO_S) {
			// single output file ?
			if (clr.clo & CLO_E) {
				assert(clr.count_input_files == (size_t) 1);
				
				file_copy(clr.output_file, clr.input_files[0]);
			} else {
				for (size_t i = 0; i < clr.count_input_files; i++) {
					file_copy(clr.output_files[i], clr.input_files[i]);
				}
			}
			
			goto cleanup;
		}
	}
	
	// assemble
	
	// link
	
	// clean up and exit
	cleanup:
	
	destruct_clr(&clr);
	
	return 0;
}
