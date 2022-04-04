# build slg

all: release
	make clean

SRC_FILES =           \
$(wildcard ./src/*.c)

HEADER_FILES =        \
$(wildcard ./src/*.h)

OBJ_FILES = ${SRC_FILES:.c=.o}

release: ${OBJ_FILES}
	gcc -std=c17 -Wshadow -Wall ${OBJ_FILES} -o slg -O2

%.o: %.c ${HEADER_FILES}
	gcc -std=c17 -Wshadow -Wall -c $< -o $@

.PHONY:
clean:
	find . -name *.o -delete
