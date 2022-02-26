// defines some exit codes specific for slg compilation/linking/etc.

#pragma once

#define SLG_EXIT_SUCCESSFUL        (0 << 2)
#define SLG_EXIT_BAD_ARGV          (1 << 2)
#define SLG_EXIT_FILE_ERROR        (2 << 2)
#define SLG_EXIT_SOURCE_CODE_ERROR (3 << 2)
