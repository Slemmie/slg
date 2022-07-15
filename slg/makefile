# compile slg

all: release

C_FLAGS = -Wshadow -Wall -std=c17
C_FLAGS_RELEASE = -O2
C_FLAGS_DEBUG = -g -fsanitize=address,undefined

SRC_FILES = $(wildcard ./src/*.c)

HDR_FILES = $(wildcard ./src/*.h)

OBJ_FILES_RELEASE = ${SRC_FILES:.c=__release__.o}
OBJ_FILES_DEBUG = ${SRC_FILES:.c=__debug__.o}

release: ${OBJ_FILES_RELEASE}
	gcc $(C_FLAGS) $^ -o slg $(C_FLAGS_RELEASE)

%__release__.o: %.c ${HDR_FILES}
	gcc $(C_FLAGS) -c $< -o $@ $(C_FLAGS_RELEASE)

debug: ${OBJ_FILES_DEBUG}
	gcc $(C_FLAGS) $^ -o slg $(C_FLAGS_DEBUG)

%__debug__.o: %.c ${HDR_FILES}
	gcc $(C_FLAGS) -c $< -o $@ $(C_FLAGS_DEBUG)

.PHONY: clean
clean:
	find . -name *.o -delete
