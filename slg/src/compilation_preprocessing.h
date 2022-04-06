// functions used by compiler to prepare raw input file for easier tokanizing

#pragma once

void check_balanced_brackets(const char* input_buffer);

// assumes an even number of "'" characters in the passed buffer
// supports \n, \t and \0
void replace_charconstexpr(char** input_buffer);
