GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
LINT     = lint -Xa -fd -m -u -x -errchk=%all

CSOURCE  = bcat.c
EXECBIN  = bcat
SOURCES  = ${CSOURCE} Makefile README
LISTING  = Listing.bcat.ps
SUBMITDIR  = cmps012b-wm.w12 lab4

all : ${EXECBIN}

${EXECBIN} : ${CSOURCE}
	${GCC} ${CSOURCE} -o ${EXECBIN}

lint : ${CSOURCE}
	checksource ${SOURCES}
	${LINT} ${CSOURCE}

ci : ${SOURCES}
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBIN}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}

again :
	gmake --no-print-directory spotless ci lint all lis
