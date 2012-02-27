# $Id: Makefile,v 1.4 2012-02-14 20:44:24-08 - - $
MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS   = gcc -MM
LINT     = lint -Xa -fd -m -u -x -errchk=%all

CHEADER   =        intx.h
CSOURCE   = main.c intx.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = intx
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}
LISTSRC   = ${SOURCES} ${DEPSFILE}
LISTING   = Listing.intx.ps

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	${GCC} -c $<

lint : ${CSOURCE}
	${LINT} ${CSOURCE}
	checksource ${CSOURCE}

ci : ${SOURCES}
	cid + ${SOURCES}

ident : ${SOURCES}
	ident ${SOURCES}

lis : ${SOURCES} test
	mkpspdf ${LISTING} ${LISTSRC} test*.lis

clean :
	- rm ${OBJECTS} ${DEPSFILE} core test*.lis

spotless : clean
	- rm ${EXECBIN}

test : ${EXECBIN}
	runprogram.perl -x testa.lis ${EXECBIN}
	valgrind --leak-check=full ${EXECBIN} >testb.lis 2>&1

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps

again :
	gmake spotless deps ci lint all lis

ifeq ("${NEEDINCL}","")
include ${DEPSFILE}
endif

