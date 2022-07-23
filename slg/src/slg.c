// entry point

#include "parse_command_line.h"
#include "error.h"
#include "slg_compile.h"

int main(int argc, char** argv) {
	// initialize things
	init_errors();
	
	// parse command line
	Command_line_result clr = construct_clr(argc, argv);
	
	// compile each *slg* input file
	if (!slg_compile_stage(&clr)) {
		goto cleanup;
	}
	
	// assemble
	
	// link
	
	// clean up and exit
	cleanup:
	
	destruct_clr(&clr);
	
	return 0;
}
