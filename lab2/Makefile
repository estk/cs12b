JAVASRC = exit255.java
SOURCES = Makefile ${JAVASRC}
MAINCLASS = exit255
CLASSES = exit255.class
JARFILE = exit255
JARCLASSES = ${CLASSES}

all: ${JARFILE}

${JARFILE}: ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class: %.java
	javac $<

clean:
	- rm ${CLASSES}

check: ${SOURCES}
	- checksource ${SOURCES}

test: ${JARFILE}
	- (( ${JARFILE} 2>&1 ) > 255.output \
	; echo $$? >> 255.output )
