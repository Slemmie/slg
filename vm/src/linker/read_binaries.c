// implementation of creating a list of buffers from a list of input binary files

#include "../util/read_file.h"

#include <stddef.h>
#include <stdlib.h>

void** read_binaries(const char** filepaths, size_t count) {
	// firstly, if there are no input files at all
	if (!count) {
		return NULL;
	}
	
	// now allocate first dimension
	void** result = malloc(sizeof(void*) * count);
	
	// if malloc failed
	if (!result) {
		return NULL;
	}
	
	// then allocate and fill each of the buffers
	for (size_t i = 0; i < count; i++) {
		result[i] = read_binary(filepaths[i]);
		
		// if something went wrong...
		if (!result[i]) {
			// free the already allocated sources
			for (size_t j = 0; j < i; j++) {
				free(result[i]);
			}
			
			// then free the outer dimension
			free(result);
			
			return NULL;
		}
	}
	
	// finally, we successfully return
	// everything should be in order
	return result;
}
