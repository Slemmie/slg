// slg entry point

#include "parse_argv.h"
#include "tmp_dir_manager.h"
#include "compile.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	// 1. parse command line arguments
	Argv_info argv_info;
	parse_argv(&argv_info, argc, argv);
	
	// 2. configure tmp directory
	create_tmp_dir();
	
	// 3. perform compilation
	for (size_t i = 0; i < argv_info.input_file_count; i++) {
		if (argv_info.input_file_types[i] == ARGV_FILE_TYPE_SLG) {
			char* next_file_path = NULL;
			create_file_of(argv_info.input_file_paths_prefix[i], ".asm", next_file_path);
			compile(argv_info.input_file_paths[i], next_file_path);
			free(argv_info.input_file_paths[i]);
			argv_info.input_file_paths[i] = next_file_path;
			argv_info.input_file_types[i] = ARGV_FILE_TYPE_ASM;
			free(argv_info.input_file_paths_suffix[i]);
			argv_info.input_file_paths_suffix[i] = malloc(sizeof(char) * 5);
			strcpy(argv_info.input_file_paths_suffix[i], ".asm");
		}
	}
	
	// 4. perform assembling
	if (argv_info.output_file_type == ARGV_FILE_TYPE_ASM) {
		destruct_argv_info(&argv_info);
		clean_exit(0);
	}
	// ...
	
	// 5. perform linking
	if (argv_info.output_file_type == ARGV_FILE_TYPE_OBJ) {
		destruct_argv_info(&argv_info);
		clean_exit(0);
	}
	// ...
	
	// 6. clean up
	destruct_argv_info(&argv_info);
	clean_exit(0);
}
