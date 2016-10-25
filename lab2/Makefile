JAVASRC = exit255.java
SOURCES = README Makefile ${JAVASRC}
MAINCLASS = exit255
CLASSES = exit255.class
JARFILE = exit255
JARCLASSES = ${CLASSES}

all: ${JARFILE}

${JARFILE}: ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm -vf Manifest
	chmod +x ${JARFILE}

%.class: %.java
	javac $<

test: ${JARFILE}
	(${JARFILE} 2>&1; echo EXIT STATUS = $$?) >255.output
