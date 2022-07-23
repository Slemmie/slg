// implements generate_temp_file.h

#include "generate_temp_file.h"

#include "error.h"
#include "random_util.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char* generate_temp_file(const char* base_path, const char* new_extension) {
	const char* temp_dir = get_slg_temp_dir();
	
	char* rnd_hex_str = get_rand_rex_str(16);
	
	size_t len = strlen(temp_dir) + strlen(base_path) + strlen(new_extension) + strlen(rnd_hex_str);
	
	char* result = malloc(sizeof(char) * (len + 1));
	
	if (!result) {
		free(rnd_hex_str);
		internal_fatal_error("malloc failed");
	}
	
	memset(result, 0, (len + 1));
	memcpy(result, temp_dir, strlen(temp_dir));
	strcat(result, base_path);
	strcat(result, rnd_hex_str);
	strcat(result, new_extension);
	
	free(rnd_hex_str);
	
	if (!access(result, F_OK)) {
		internal_fatal_error("auto generated temporary file '%s' already exists", result);
	}
	
	FILE* file = fopen(result, "w");
	
	if (!file) {
		internal_fatal_error("failed to create file '%s'", result);
	}
	
	fclose(file);
	
	return result;
}
