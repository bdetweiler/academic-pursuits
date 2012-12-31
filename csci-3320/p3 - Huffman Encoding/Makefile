
CC=g++
LDFLAGS=-Wall
CXXFLAGS=-Wall
TARGETS=huffman

all: ${TARGETS}

clean:
	-rm -f *.o ${TARGETS} *.huff

# For testing purposes
test: test.o tree.o util.o

test.o: test.cpp


huffman: huffman.o codes.o util.o tree.o 

huffman.o: huffman.cpp tree.h codes.h 
codes.o: codes.cpp codes.h tree.h util.h dheap.h
# list.o: list.cpp list.h
tree.o: tree.cpp tree.h util.h
util.o: util.cpp util.h

