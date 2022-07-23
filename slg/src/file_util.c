// implements file_util.h

#include "file_util.h"

#include "error.h"

#include <stdio.h>
#include <stdlib.h>

void file_copy(const char* dest_path, const char* source_path) {
	FILE* dest_file = fopen(dest_path, "w");
	
	if (!dest_file) {
		fatal_error("failed to open file '%s'", dest_path);
	}
	
	FILE* source_file = fopen(source_path, "r");
	
	if (!source_file) {
		fclose(dest_file);
		fatal_error("failed to open file '%s'", source_path);
	}
	
	fseek(source_file, 0, SEEK_END);
	long source_length = ftell(source_file);
	fseek(source_file, 0, SEEK_SET);
	
	char* source_contents = malloc(sizeof(char) * (source_length + 1));
	
	if (!source_contents) {
		internal_fatal_error("malloc failed");
	}
	
	size_t items_read = fread(source_contents, source_length, 1, source_file);
	source_contents[source_length] = '\0';
	
	if (items_read != (size_t) source_length) {
		fclose(dest_file);
		fclose(source_file);
		internal_fatal_error("unexpected number of bytes read from '%s'", source_path);
	}
	
	size_t items_written = fwrite(source_contents, source_length, 1, dest_file);
	
	if (items_written != items_read) {
		fclose(dest_file);
		fclose(source_file);
		internal_fatal_error("unexpected number of bytes written to '%s'", source_path);
	}
	
	fclose(dest_file);
	fclose(source_file);
	
	free(source_contents);
}
