GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
CSOURCE   = l8stat.c
EXECBIN   = l8stat

all : ${EXECBIN}

${EXECBIN} : ${CSOURCE}
	${GCC} ${CSOURCE} -o ${EXECBIN}

%.c : ${EXECBIN}
