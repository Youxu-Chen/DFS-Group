CC=gcc
CFLAGS=-g

SRC_CORR=corr.h corr.o

all: test

corr.o:	corr.c
	${CC} -c corr.c -o corr.o ${CFLAGS}

test:	test.c ${SRC_CORR}
	${CC} test.c corr.o -o test ${CFLAGS}

.PHONY:
clean:
	-rm -rf *.o
	-rm test
