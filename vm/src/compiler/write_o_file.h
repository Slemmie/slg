// going from token list to .o file

#pragma once

#include "token.h"

// take a path to the output file along with a token list and generate a .o format file
void write_o_file(const char* output_file, Token_list* token_list);
