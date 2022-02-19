// "entry point" of the compiler module

// outputs a .o file, takes exactly one source code file
// .o file contains:
//   a list of unresolved symbols
//   a list of resolved symbols with their implementations
// implementations are a sequence of instructions, structured much like assembly

// for now, we do not support flags/debug-modes/etc.

#pragma once

// returns 0 if nothing went wrong
// the function takes care of potential error printing itself
extern int compile(const char* output_file, const char* input_file);
