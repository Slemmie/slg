// entry point

#include "parse_command_line.h"

int main(int argc, char** argv) {
	// parse command line
	Command_line_result clr = construct_clr(argc, argv);
	
	// compile each input file
	
	// assemble
	
	// link
	
	// clean up and exit
	destruct_clr(&clr);
	
	return 0;
}
