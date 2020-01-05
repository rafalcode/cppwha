CC=g++
CFLAGS=-g -Wall
EXECUTABLES=expdi0 expdi1 ss0 ss1 v2d0

expdi0: expdi0.cpp
	${CC} ${CFLAGS} -o $@ $^

expdi1: expdi1.cpp
	${CC} ${CFLAGS} -o $@ $^

v2d0: v2d0.cpp
	${CC} ${CFLAGS} -o $@ $^

# stringstream
#
# obs! 
# experiment abandoned
# there is precision() and also the following link is decent worth further study.
# https://stackoverflow.com/questions/2839592/equivalent-of-02d-with-stdstringstream
ss0: ss0.cpp
	${CC} ${CFLAGS} -o $@ $^

ss1: ss1.cpp
	${CC} ${CFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
