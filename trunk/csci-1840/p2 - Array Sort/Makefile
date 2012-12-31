.SUFFIXES:  # Clear all built in suffix rules

array_sort: array_sort.o
	gcc -Wall $^ -o $@
array_sort.o: array_sort.c
	gcc -Wall -c $<
clean:
	rm -f *.o array_sort
