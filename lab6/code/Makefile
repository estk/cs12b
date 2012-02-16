# $Id: Makefile,v 1.5 2011-10-26 19:15:04-07 - - $

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
LINT     = lint -Xa -fd -m -u -x -errchk=%all

CSOURCES = nsort.c lsort.c
SOURCES  = ${CSOURCES} Makefile
EXECBINS = nsort   lsort
LISTING  = ../lab6c.nsort-lsort.ps
SUBMIT   = submit cmps012b-wm.f11 lab6

all : ${EXECBINS}

% : %.c
	- checksource $<
	- ${LINT} $<
	${GCC} $< -o $@

ci :
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

lis : ${CSOURCES} Makefile
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

