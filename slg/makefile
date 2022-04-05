# build slg

all: release
	make clean

SRC_FILES =           \
$(wildcard ./src/*.c)

HEADER_FILES =        \
$(wildcard ./src/*.h)

OBJ_FILES = ${SRC_FILES:.c=.o}
OBJ_FILES_DBG = ${SRC_FILES:.c=_debug.o}

release: ${OBJ_FILES}
	gcc -std=c17 -Wshadow -Wall ${OBJ_FILES} -o slg -O2

%.o: %.c ${HEADER_FILES}
	gcc -std=c17 -Wshadow -Wall -c $< -o $@ -O2

debug: ${OBJ_FILES_DBG}
	gcc -std=c17 -Wshadow -Wall ${OBJ_FILES_DBG} -o slg -g -fsanitize=address -fsanitize=undefined
	make clean

%_debug.o: %.c ${HEADER_FILES}
	gcc -std=c17 -Wshadow -Wall -c $< -o $@ -g -fsanitize=address -fsanitize=undefined

.PHONY:
clean:
	find . -name *.o -delete
