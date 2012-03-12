GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
CSOURCE   = numsort.c linesort.c inssort.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = numsort linesort
SUBMITS   = README Makefile
PROJECT   = cmps012b-wm.w12 lab9
LINT      = lint -Xa -fd -m -u -x -errchk=%all

all : numsort linesort

numsort : numsort.o inssort.o

linesort : linesort.o inssort.o

%.o : %.c
	${GCC} -c $<

lint : ${CSOURCE}
	${LINT} ${CSOURCE}

ci : ${CSOURCE}
	checksource ${CSOURCE}
	ci ${CSOURCE}

submit : ${CSOURCE} ${SUBMITS}
	submit ${PROJECT} ${CSOURCE}
	submit ${PROJECT} ${SUBMITS}

#${EXECBIN} : ${CSOURCE}
	#${GCC} ${CSOURCE} -o ${EXECBIN}

