// slg entry point

#include "parse_argv.h"
#include "tmp_dir_manager.h"

int main(int argc, char** argv) {
	// 1. parse command line arguments
	Argv_info argv_info;
	parse_argv(&argv_info, argc, argv);
	
	// 2. configure tmp directory
	create_tmp_dir();
	
	// 3. perform compilation
	
	// 4. perform assembling
	
	// 5. perform linking
	
	// 6. clean up
	destruct_argv_info(&argv_info);
	clean_exit(0);
}
