JAVASRC = jgrep.java messages.java options.java
SOURCES = README Makefile ${JAVASRC}
MAINCLASS = jgrep
CLASSES = jgrep.class messages.class options.class
JARFILE = jgrep
JARCLASSES = ${CLASSES}

all: ${JARFILE}

${JARFILE}: ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm -vf Manifest
	chmod +x ${JARFILE}

%.class: %.java
	javac $<

clean:
	- rm -vf ${CLASSES} test.output

spotless: clean
	- rm -vf ${JARFILE}

ci: ${SOURCES}
	cid + ${SOURCES}
	- checksource ${SOURCES}

test: ${JARFILE}
	(${JARFILE} 2>&1; echo EXIT STATUS = $$?) >test.output
	cat -nv test.output

again:
	gmake --no-print-directory spotless ci all test
