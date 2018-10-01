CC=g++
CFLAGS=-g -Wall
EXECUTABLES=expdi0 expdi1

expdi0: expdi0.cpp
	${CC} ${CFLAGS} -o $@ $^

expdi1: expdi1.cpp
	${CC} ${CFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
