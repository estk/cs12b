# $Id: Makefile,v 1.3 2012-03-06 18:41:37-08 - - $

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
GMAKE     = gmake --no-print-directory

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
LINT      = lint -Xa -fd -m -u -x -errchk=%all

CSOURCE   = debugf.c stack.c bigint.c token.c main.c
CHEADER   = debugf.h stack.h bigint.h token.h
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = a5dc
SUBMITS   = ${CHEADER} ${CSOURCE} ${MKFILE}
SOURCES   = ${SUBMITS}
LISTING   = Listing.code.ps
PROJECT   = cmps012b-wm.w12 asg5

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	${GCC} -c $<

lint : ${CSOURCE}
	${LINT} ${CSOURCE}
	checksource ${SUBMITS}

ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SUBMITS}

lis : ${SOURCES} ${DEPSFILE}
	mkpspdf ${LISTING} ${SOURCES} ${DEPSFILE}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core ${EXECBIN}.errs

spotless : clean
	- rm ${EXECBIN}

submit : ${SUBMITS}
	submit ${PROJECT} ${SUBMITS}

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${GMAKE} deps

again :
	${GMAKE} spotless deps ci lint all lis

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

