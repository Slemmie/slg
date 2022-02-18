// implementation of logging help

#pragma once

#include <stdio.h>

// help section for using command line arguments proporly
void pr_help_argv() {
	printf("|- slg command-line help section -|\n");
	printf("- Help page accessable with '-h' flag\n");
	printf("- Execution:\n");
	printf("  - Usage: $ slg -r <executable>\n");
	printf("  - No other flags can be passed in run mode\n");
	printf("- Compilation/Linking:\n");
	printf("  - Usage: $ slg <flags> <input files>\n");
	printf("    - Flags and input file can be in any order\n");
	printf("  - Flags:\n");
	printf("    - '-r' Used for run mode, cannot be used during compilation/linking\n");
	printf("    - '-h' Used for diplaying this help section, cannot be used during compilation/linking\n");
	printf("    - '-o' Used to specify the output file name\n");
	printf("      - Desired file name should follow immediately after the flag\n");
	printf("      - If unset, the output file name defaults to 'a.out'\n");
	printf("  - Anything else is interpreted as an input file, and must therefore exist\n");
	printf("  - If the specified output file has a '.o' extension, only one input file may be passed, and a linking does not occur\n");
	printf("  - If all input files have a '.o' extension, linker mode will be envoked\n");
	printf("  - If input files do not have a '.o' extension, but a non-'.o' extension ouput file is specified, the input files will be compiled and then linked at once\n");
	printf("- NOTE: for now, very few features exist, for instance, no '-c' flag exists\n");
}
