# $Id: Makefile,v 1.2 2012-02-21 19:53:04-08 - - $

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
LINT      = lint -Xa -fd -m -u -x -errchk=%all

EXECBIN   = hashfn
HASHSRC   = hashfn.c ../code/strhash.c
LISFILES  = hashfn.c ../code/strhash.h ../code/strhash.c \
	    Makefile pspell.perl
LISTING   = Listing.misc.ps
HASHOUT   = hashfn.out

TESTDATA  = 0 9 A Z a z foo bar baz qux \
            quux quuux quuuux quuuuux quuuuuux quuuuuuux quuuuuuuux

all : ${EXECBIN}

% : %.c
	- cid + $<
	- checksource $<
	${GCC} -o $@ ${HASHSRC}

lint : ${HASHSRC}
	- ${LINT} ${HASHSRC}

ci : ${LISFILES}
	- checksource ${LISFILES}
	- cid + ${LISFILES}

lis : ${LISFILES} ${HASHOUT}
	mkpspdf ${LISTING} ${LISFILES} ${HASHOUT}

${HASHOUT} : hashfn
	hashfn ${TESTDATA} * >${HASHOUT}

spotless :
	- rm ${EXECBIN} ${HASHOUT}

