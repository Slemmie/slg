# build slg

all: release
	make clean

C_FLAGS = -std=c17 -Wshadow -Wall
C_RELEASE_FLAGS = -O2
C_DEBUG_FLAGS = -g -fsanitize=address -fsanitize=undefined

SRC_FILES =           \
$(wildcard ./src/*.c)

HEADER_FILES =        \
$(wildcard ./src/*.h)

OBJ_FILES = ${SRC_FILES:.c=.o}
OBJ_FILES_DBG = ${SRC_FILES:.c=_debug.o}

release: ${OBJ_FILES}
	gcc $(C_FLAGS) ${OBJ_FILES} -o slg $(C_RELEASE_FLAGS)

%.o: %.c ${HEADER_FILES}
	gcc $(C_FLAGS) -c $< -o $@ $(C_RELEASE_FLAGS)

debug: ${OBJ_FILES_DBG}
	gcc $(C_FLAGS) ${OBJ_FILES_DBG} -o slg $(C_DEBUG_FLAGS)
	make clean

%_debug.o: %.c ${HEADER_FILES}
	gcc $(C_FLAGS) -c $< -o $@ -g $(C_DEBUG_FLAGS)

.PHONY:
clean:
	find . -name *.o -delete
