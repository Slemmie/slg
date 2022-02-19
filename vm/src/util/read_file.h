// contains utility for reading files into buffers

#include <stdio.h>
#include <stdlib.h>

char* read_source(const char* filepath) {
	FILE* file = fopen(filepath, "r");
	
	// if we fail to open, return NULL and let our caller deal with error handling
	if (!file) {
		return NULL;
	}
	
	// aquire needed buffer size
	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	// read contents
	char* buffer = malloc(file_size + 1);
	// if malloc fails, return NULL ans let our caller deal with error handling
	if (!buffer) {
		return NULL;
	}
	size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
	// if file size and bytes read do not match, we have an error, let caller deal with error handling
	if (bytes_read != file_size) {
		return NULL;
	}
	buffer[file_size] = '\0';
	
	fclose(file);
	
	return buffer;
}
