# $Id: Makefile,v 1.1 2012-01-05 19:21:49-08 - - $

JAVASRC    = jfmt.java
SOURCES    = ${JAVASRC} Makefile README
MAINCLASS  = jfmt
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES}
JARFILE    = jfmt
SUBMITDIR  = cmps012b-wm.w12 asg1
LISTING    = asg1j-jfmt.code.ps

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	cid + $<
	javac $<
	checksource $<

clean :
	- rm ${JARCLASSES} test.output

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	cid + ${SOURCES} test.input
	checksource ${SOURCES}

lis : all
	${JARFILE} test.input >test.output
	mkpspdf ${LISTING} ${SOURCES} test.input test.output

submit : ${SOURCES} ci
	submit ${SUBMITDIR} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless lis
	
