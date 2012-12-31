TARGETS=main

CC=gcc
CFLAGS=-Wall -Ilib/
LDFLAGS=-Wall -Llib/
LDLIBS=-lqueue

all: $(TARGETS)
	strip $(TARGETS)
clean:
	rm -f *.o $(TARGETS)

# to use the implicit linking the root of the target
# MUST match the first dependancy

main: main.o
main.o: main.c

