rat: main.o rat.o
	g++ -Wall main.o rat.o -o rat
main.o: main.cpp rat.h
	g++ -Wall -c main.cpp
rat.o: rat.cpp rat.h
	g++ -Wall -c rat.cpp
war:
	g++ --version
clean:
	rm -f *.o rat
