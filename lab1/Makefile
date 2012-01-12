# $Id: Makefile,v 1.4 2011-09-29 16:11:14-07 - - $
JAVASRC = hello.java
SOURCES = README Survey Makefile ${JAVASRC}
MAINCLASS = hello
CLASSES = hello.class
JARFILE = hello
JARCLASSES = ${CLASSES}
SUBMITDIR = cmps012b-wm.w12 lab1

all: ${JARFILE}

${JARFILE}: ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class: %.java
	- cid + $<
	javac $<

clean:
	- rm ${CLASSES} test.output

spotless: clean
	- rm ${JARFILE}
	- ls -ago

ci: ${SOURCES}
	cid + ${SOURCES}

check: ${SOURCES}
	- checksource ${SOURCES}

test: ${JARFILE}
	( echo "%%%%%%%% ${JARFILE}" ; ${JARFILE} 2>&1 \
	; echo "%%%%%%%% Exit status = $$?" \
	; echo "%%%%%%%% uname -a" ; uname -a \
	)>test.output
	cat - nv test.output

submit: check ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}
	- testsubmit ${SUBMITDIR} ${SOURCES}

again:
	gmake --no-print-directory spotless ci all test check
