.SUFFIXES:      # clear all built in suffix rules
all: convert calc

convert: convert.o
	g++ -Wall convert.o -o convert
calc: calc.o
	g++ -Wall calc.o -o calc
convert.o: convert.cpp stack.h
	g++ -Wall -c convert.cpp
calc.o: calc.cpp stack.h
	g++ -Wall -c calc.cpp
clean:
	rm -f *.o convert calc
