// implements util/file_io.h

#include "file_io.h"

#include "../tmp_dir_manager.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* read_file(const char* filepath) {
	FILE* file = fopen(filepath, "r");
	
	if (!file) {
		printf("[fatal]: failed to read file '%s'\n", filepath);
		clean_exit(1);
	}
	
	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	rewind(file);
	
	char* buffer = malloc(file_size + 1);
	long bytes_read = fread(buffer, file_size, sizeof(char), file);
	buffer[file_size] = '\0';
	
	if (bytes_read != file_size) {
		printf("[warning]: mismatch in file size and bytes read of file '%s'\n", filepath);
		clean_exit(1);
	}
	
	fclose(file);
	
	return buffer;
}

void write_file(const char* filepath, const char* buffer) {
	FILE* file = fopen(filepath, "w");
	
	if (!file) {
		printf("[fatal]: failed to write file '%s'\n", filepath);
		clean_exit(1);
	}
	
	fwrite(buffer, strlen(filepath), sizeof(char), file);
	
	fclose(file);
}
