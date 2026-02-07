# texpand - dumb, fast tex macro map to unicode

.POSIX:

PREFIX ?= /usr/local

CC = cc
CFLAGS = -std=c99 -O3 -Wall -Wextra -Wpedantic
GFLAGS = --struct-type --lookup-function-name=table --readonly-tables --omit-struct-type

SOURCE = table.c texpand.c
OBJECTS = ${SOURCE:.c=.o}
TARGET = texpand
GPERF = table.gperf

all: ${TARGET}

table.c: ${GPERF}
	gperf ${GFLAGS} $< > $@

.c.o:
	${CC} -c ${CFLAGS} $<

${TARGET}: ${OBJECTS}
	${CC} -o $@ ${OBJECTS}

clean:
	rm -f ${TARGET} ${OBJECTS} table.c

install: all
	mkdir -p "${DESTDIR}${PREFIX}/bin"
	cp -f texpand "${DESTDIR}${PREFIX}/bin"
	chmod 755 "${DESTDIR}${PREFIX}/bin/texpand"

uninstall:
	rm -f "${DESTDIR}${PREFIX}/bin/texpand"

.PHONY: all clean install uninstall
