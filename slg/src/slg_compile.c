// implements slg_compile.h

#include "slg_compile.h"

#include "error.h"
#include "generate_temp_file.h"
#include "file_util.h"

#include <stdlib.h>
#include <string.h>

int slg_compile_stage(Command_line_result* clr) {
	for (size_t i = 0; i < clr->count_input_files; i++) {
		if (clr->input_files_format[i] == FF_SLG) {
			char* next_file_name = generate_temp_file(clr->input_file_no_ext[i], ".asm");
			
			//slg_compile(clr.input_files[i], next_file_name);
			
			free(clr->input_files[i]);
			size_t len = strlen(next_file_name);
			clr->input_files[i] = malloc(sizeof(char) * (len + 1));
			if (!clr->input_files[i]) {
				internal_fatal_error("malloc failed");
			}
			
			memcpy(clr->input_files[i], next_file_name, len);
			clr->input_files[i][len] = '\0';
			
			free(next_file_name);
			
			clr->input_files_format[i] = FF_ASM;
		}
	}
	
	// if we are to stop at this stage...
	// copy the files from their temporary location
	if (clr->clo & CLO_S) {
		// single output file ?
		if (clr->clo & CLO_E) {
			if (clr->count_input_files != (size_t) 1) {
				internal_fatal_error("bad value");
			}
			
			file_copy(clr->output_file, clr->input_files[0]);
		} else {
			for (size_t i = 0; i < clr->count_input_files; i++) {
				file_copy(clr->output_files[i], clr->input_files[i]);
			}
		}
		
		return 0;
	}
	
	return 1;
}
