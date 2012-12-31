.SUFFIXES:  # Clear all built in suffix rules

wfc: word.o list.o main.o
	g++ -Wall $^ -o $@
word.o: word.cpp word.h
	g++ -Wall -c $<
list.o: list.cpp list.h
	g++ -Wall -c $<
main.o: main.cpp
	g++ -Wall -c $<
clean:
	rm -f *.o wfc
