.SUFFIXES:  # Clear all built in suffix rules

proc_queue: proc_queue.o process.o
	g++ -Wall $^ -o $@
proc_queue.o: proc_queue.cpp 
	clear
	g++ -Wall -c $<
process.o: process.cpp
	g++ -Wall -c $<
clean:
	rm -f *.o proc_queue
