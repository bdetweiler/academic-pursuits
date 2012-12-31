.SUFFIXES:  # Clear all built in suffix rules

pow4: pow4.o
	gcc -Wall $^ -o $@
pow4.o: pow4.c
	gcc -Wall -c $<
clean:
	rm -f *.o pow4
