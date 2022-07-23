// entry point for slg_comile()

#pragma once

#include "parse_command_line.h"

// calls slg_compile appropriately and handles setup
// returns zero if the functions fails (and doesn't exit) or if compilation was the final stage
int slg_compile_stage(Command_line_result* clr);
