# $Id: Makefile,v 1.11 2014-02-13 18:53:02-08 - - $

MKFILE    = Makefile
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
GRIND    = valgrind --leak-check=full

CHEADER   = cmatch.h
CSOURCE   = cmatch.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = cmatch
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core test.lis

spotless : clean
	- rm ${EXECBIN} ${LISTING:.ps=.p*} test.lis

test : ${EXECBIN}
	${GRIND} --log-file=test.log ${EXECBIN} >test.out 2>test.err
	more ${DEPSFILE} test.out test.err test.log >test.lis
	- rm test.out test.err test.log

ifeq ("${NEEDINCL}","")
endif

