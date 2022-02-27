// implementation of prototypes from read_file.h

#include "read_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

// we store the size of the file in the first sizeof(uint64_t) bytes
void* read_binary(const char* filepath) {
	FILE* file = fopen(filepath, "rb");
	
	// if we fail to open, return NULL and let our caller deal with error handling
	if (!file) {
		return NULL;
	}
	
	// aquire needed buffer size
	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	// read contents
	void* buffer = malloc(file_size + sizeof(uint64_t));
	// if malloc fails, return NULL ans let our caller deal with error handling
	if (!buffer) {
		return NULL;
	}
	size_t bytes_read = fread(((char*)buffer) + sizeof(uint64_t), sizeof(char), file_size, file);
	// if file size and bytes read do not match, we have an error, let caller deal with error handling
	if (bytes_read != file_size) {
		return NULL;
	}
	
	// set the file size
	*((uint64_t*) buffer) = file_size;
	
	fclose(file);
	
	return buffer;
}
