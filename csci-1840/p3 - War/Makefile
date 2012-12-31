TARGETS=war

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall

all: $(TARGETS)
clean:
	rm -f *.o $(TARGETS)

# to use the implicit linking the root of the target
# MUST match the first dependancy

war: queue.o war.o
war.o: war.c war.h queue.h 
queue.o: queue.c queue.h
