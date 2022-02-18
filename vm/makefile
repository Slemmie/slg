# makefile for compiling slg - targeting linux
# gcc compiler used, and must be available

# standard usage: $ make
# make sure not to have any existing '.o' in your build directory

# simple release build is standard for now
all: release

# flags used
C_FLAGS = -std=c17 -Wshadow -Wall 
C_RELEASE_FLAGS = -O2
C_DEBUG_FLAGS = -g -fsanitize=address -fsanitize=undefined

# full path to root
ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

# list of source files
COMPILER_SRC_FILES =
LINKER_SRC_FILES =
RUNNER_SRC_FILES =
SRC_FILES = \
$(ROOT_DIR)/src/slg.c \
$(COMPILER_SRC_FILES) \
$(LINKER_SRC_FILES)   \
$(RUNNER_SRC_FILES)

# trailing flags - used whenever we call this makefile within itself
C_TRAL_FLAGS =

# release target - current default - gets run 'all' target
release:
	C_TRAIL_FLAGS_ARG="$(C_RELEASE_FLAGS)"; \
	for file in $(SRC_FILES); do \
		make $${file}                          \
		C_TRAIL_FLAGS="$${C_TRAIL_FLAGS_ARG}"; \
	done;
	gcc $(C_FLAGS) *.o -o slg $(C_RELEASE_FLAGS)
	rm *.o

# debug target
debug:
	C_TRAIL_FLAGS_ARG="$(C_DEBUG_FLAGS)"; \
	for file in $(SRC_FILES); do \
		make $${file}                          \
		C_TRAIL_FLAGS="$${C_TRAIL_FLAGS_ARG}"; \
	done;
	gcc $(C_FLAGS) *.o -o slg $(C_DEBUG_FLAGS)
	rm *.o

# specific compilation of each source file - most are exactly alike
.PHONY: $(ROOT_DIR)/src/slg.c
$(ROOT_DIR)/src/slg.c:
	gcc $(C_FLAGS) $@ -c $(C_TRAIL_FLAGS)
