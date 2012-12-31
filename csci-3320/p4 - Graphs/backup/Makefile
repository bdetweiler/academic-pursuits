CC=g++
LDFLAGS=-Wall 
CXXFLAGS=-Wall
TARGETS=ospf

all: ${TARGETS}

clean:
	-rm -f *.o ${TARGETS}


ospf:  ospf.o
	g++ $(LDFLAGS) $^ -o $@
graph.o: graph.cpp graph.h
	clear
	g++ $(CXXFLAGS) -c $<
ospf.o: ospf.cpp
	g++ $(CXXFLAGS) -c $<
list.o: list.cpp
	g++ $(CXXFLAGS) -c $<
