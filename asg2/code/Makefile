# $Id: Makefile,v 1.3 2012-01-19 19:14:44-08 - - $

JAVASRC    = jxref.java listmap.java intqueue.java
SOURCES    = ${JAVASRC} Makefile README
MAINCLASS  = jxref
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES} \
             intqueue\$$1.class listmap\$$1.class \
             intqueue\$$itor.class listmap\$$itor.class \
             intqueue\$$node.class listmap\$$node.class
JARFILE    = jxref
LISTING    = ../asg2j-jxref.code.ps
SUBMITDIR  = cmps012b-wm.w12 asg2

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	chmod +x ${JARFILE}

%.class : %.java
	- checksource $<
	- cid + $<
	javac $<

clean :
	- rm ${JARCLASSES} Manifest

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	- checksource ${SOURCES}
	cid + ${SOURCES}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis
	
