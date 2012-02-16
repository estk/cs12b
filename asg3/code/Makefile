# $Id: Makefile,v 1.1 2012-02-07 15:43:17-08 - - $

JAVASRC    = airport.java treemap.java
SOURCES    = ${JAVASRC} Makefile README
MAINCLASS  = airport
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES} treemap\$$tree.class
JARFILE    = airport
LISTING    = ../asg3j-airport.code.ps

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	- checksource $<
	javac $<

clean :
	- rm ${JARCLASSES}

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	- checksource ${SOURCES}
	cid + ${SOURCES}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	submit cmps012b-wm.w12 asg3 ${SOURCES}
	
again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

