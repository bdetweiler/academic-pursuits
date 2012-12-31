TARGETS=enigma

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall
# LDLIBS=-lm

all: $(TARGETS)
clean:
	rm -f *.o $(TARGETS)

# to use the implicit linking the root of the target
# MUST match the first dependancy


enigma: main.o spindle.o rotor.o reflector.o# enigma.o 
main.o: main.c spindle.o # enigma.h
# enigma.o: enigma.c enigma.h rotor.h reflector.h 
spindle.o: spindle.c spindle.h reflector.h rotor.h 
reflector.o: reflector.c reflector.h 
rotor.o: rotor.c rotor.h

test:
	gcc -Wall test_rotor.c rotor.c reflector.c spindle.c
