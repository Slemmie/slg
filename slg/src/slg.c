// slg entry point

#include "parse_argv.h"
#include "tmp_dir_manager.h"

int main(int argc, char** argv) {
	// parse command line arguments
	Argv_info argv_info;
	parse_argv(&argv_info, argc, argv);
	
	// configure tmp directory
	create_tmp_dir();
	
	// sort out input file(s) and output file
	
	// perform compilation
	
	// perform assembling
	
	// perform linking
	
	// clean up
	destruct_argv_info(&argv_info);
	
	clean_exit(0);
}
