// "entry point" of the linker module

#pragma once

// linker will look for all symbols, write a list of them

// then take note of the required label "start"

// then look for definitions of all the symbols, make sure they each are there exactly once

// then writes first draft of all translation units,
// where symbols are replaces with the ips (currently all 0s)
// except for the definitions which just end up with the TOK_LABEL instruction

// then adds instruction pointers to each of the symbols, AFTER writing first draft
// so that the ips match with the new layout of the instructions after converting symbols to just the ips

// then replaces all occurances of the symbols with their respective instruction addresses

// we are jumping between files/translation units whenever we call an extern symbol
// from the compiler, all files/translation units end with a halt operation
// so if the source code randomly gets to the end of some random file,
// the code will halt, and still not be undefined behavior
// this also allows us to smack all the units one after the other in the final draft

// lastly we create the final draft of the entire executable
// we add a jump instruction at the very top that jumps to the entry point (start symbol)

// returns zero if nothing went wrong
// the function takes care of potential error printing itself
extern int link(const char* output_file, const char** input_files);
