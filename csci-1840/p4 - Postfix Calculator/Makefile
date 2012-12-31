TARGETS=calc

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall
LDLIBS=-lm

all: $(TARGETS)
clean:
	rm -f *.o $(TARGETS)

# to use the implicit linking the root of the target
# MUST match the first dependancy


calc: stack.o calc.o
calc.o: calc.c stack.h 
stack.o: stack.c stack.h
