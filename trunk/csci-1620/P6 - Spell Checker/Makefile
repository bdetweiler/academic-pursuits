.SUFFIXES:  # Clear all built in suffix rules

spellchk: word.o list.o tree.o main.o
	g++ -Wall $^ -o $@
word.o: word.cpp word.h
	g++ -Wall -c $<
list.o: list.cpp list.h
	g++ -Wall -c $<
tree.o: tree.cpp tree.h
	g++ -Wall -c $<
main.o: main.cpp
	g++ -Wall -c $<
clean:
	rm -f *.o spellchk
