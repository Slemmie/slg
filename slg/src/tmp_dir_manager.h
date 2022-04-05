// manages tmp dir and includes utility functions related to it

#pragma once

// create tmp directory
void create_tmp_dir();

// retrieve tmp dir
const char* get_tmp_dir();

// clean up tmp dir things, then call exit(code)
void clean_exit(int code);

// create file in tmp fir based on input file
void create_file_of(const char* of_path, const char* new_suffix, char* buffer);
