CPP=g++
CFLAGS=-g -Wall
EXECUTABLES=expdi0 expdi1 ss0 ss1 v2d0 ma spea iot sor

expdi0: expdi0.cpp
	${CPP} ${CFLAGS} -o $@ $^

expdi1: expdi1.cpp
	${CPP} ${CFLAGS} -o $@ $^

v2d0: v2d0.cpp
	${CPP} ${CFLAGS} -o $@ $^

spea: spea.cpp
	${CPP} ${CFLAGS} -o $@ $^

sor: sor.cpp
	${CPP} ${CFLAGS} -o $@ $^

iot: iot.cpp
	${CPP} ${CFLAGS} -o $@ $^

# stringstream
#
# obs! 
# experiment abandoned
# there is precision() and also the following link is decent worth further study.
# https://stackoverflow.com/questions/2839592/equivalent-of-02d-with-stdstringstream
ss0: ss0.cpp
	${CPP} ${CFLAGS} -o $@ $^

ss1: ss1.cpp
	${CPP} ${CFLAGS} -o $@ $^

ma: ma.cpp
	${CPP} ${CFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
