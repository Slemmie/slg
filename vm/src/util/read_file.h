// contains utility for reading files into buffers

#pragma once

char* read_source(const char* filepath);

// we store the size of the file in the first sizeof(uint64_t) bytes
void* read_binary(const char* filepath);
