wash: main.o queue.o
	g++ -Wall main.o queue.o -o wash
main.o:
	g++ -Wall -c main.cpp
queue.o:
	g++ -Wall -c queue.cpp
clean:
	rm -f *.o wash

	convert: convert.o
	        g++ -Wall $^ -o $@
		convert.o: convert.cpp stack.h
		        g++ -Wall -c $<
			clean:
			        rm -f *.o convert calc

