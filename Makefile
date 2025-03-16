CPP=g++
CFLAGS=-g -Wall
EXECUTABLES=expdi0 expdi1 ss0 ss1 v2d0 ma spea iot sor maz0 gmaz ar ut0 ut1 ut2 gp0 gcai gp1 wkda0 traord rnpart0

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

maz0: maz0.cpp
	${CPP} ${CFLAGS} -o $@ $^
gmaz: gmaz.cpp
	${CPP} ${CFLAGS} -o $@ $^
ar: ar.cpp
	${CPP} ${CFLAGS} -o $@ $^

# More UTF-8 enquiries.
ut0: ut0.cpp
	${CPP} ${CFLAGS} -o $@ $^
ut1: ut1.cpp
	${CPP} ${CFLAGS} -o $@ $^
ut2: ut2.cpp
	${CPP} -std=c++11 ${CFLAGS} -o $@ $^

gp0: gp0.cpp
	${CPP} ${CFLAGS} -I/usr/include/libxml2 -o $@ $^ -lxml2 

gp1: gp1.cpp
	${CPP} ${CFLAGS} -I/usr/include/libxml2 -o $@ $^ -lxml2 

gcai: gcai.cpp
	${CPP} ${CFLAGS} -o $@ $^ -lcairo -lcurl -ltinyxml2

wkda0: wkda0.cpp
	${CPP} ${CFLAGS} -o $@ $^

traord: traord.cpp
	${CPP} ${CFLAGS} -o $@ $^

rnpert0: rnpert0.cpp
	${CPP} ${CFLAGS} -o $@ $^

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
