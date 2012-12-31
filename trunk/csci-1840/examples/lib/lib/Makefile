TARGETS=test test_static test_shared
CC=gcc
CFLAGS=-Wall -I. -fpic
LDFLAGS=-Wall -L.

all: $(TARGETS)

clean:
	-rm -f *.o $(TARGETS) lib*.*

main.o: main.c stack.h
	$(CC) $(CFLAGS) -c $<
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $<

# this is the static library, we use ar to build it
lib_static.a: stack.o
	ar rcv $@ $^

# this is the shared library, we use gcc -shared to build it
# this actually passes the work to ld, but I never use
# ld, so I don't know the flags.
# all of the objects must be compiled -fpic
lib_shared.so: stack.o
	$(CC) -shared -o $@ $^

# here is the test program built all three ways
test: main.o stack.o
	$(CC) $(LDFLAGS) $^ -o $@

test_static: main.o lib_static.a
	$(CC) $(LDFLAGS) $^ -o $@ -l_static

test_shared: main.o lib_shared.so
	$(CC) $(LDFLAGS) $< -o $@ -l_shared
