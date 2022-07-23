// generate a temporary filepath
// mostly used for intermediate files

#pragma once

#include <sys/stat.h>

// get the temporary directory used globally by slg
static inline const char* get_slg_temp_dir() {
	static const char* slg_temp_dir = "/tmp/slg_temp/";
	
	static struct stat st = { 0 };
	if (stat(slg_temp_dir, &st) == -1) {
		mkdir(slg_temp_dir, 0700);
	}
	
	return slg_temp_dir;
}

// generate a temporary file with the given extension, of the given base path
char* generate_temp_file(const char* base_path, const char* new_extension);
