
TARGETS=queue

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall

all: $(TARGETS)
clean:
	rm -f *.o $(TARGETS)

# to use the implicit linking the root of the target
# MUST match the first dependancy

queue: queue.o main.o
main.o: main.c queue.h
queue.o: queue.c queue.h
