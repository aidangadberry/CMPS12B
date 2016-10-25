MKFILE    = Makefile

CSOURCE   = numsort.c linesort.c inssort.c
CHEADER   = inssort.h
SOURCES   = ${CSOURCE} ${MKFILE} ${CHEADER}
OBJECTS   = ${CSOURCE:.c=.o}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu11

all : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

numsort : numsort.o inssort.o

linesort : linesort.o inssort.o

%.o : %.c
	${GCC} $<

ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SOURCES}

submit : ${SOURCES}
	submit cmps012b-wm.s14 lab8 ${SOURCES}