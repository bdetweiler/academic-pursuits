TARGETS=socket_shared run
CC=gcc
CFLAGS=-Wall -I. -fpic
LDFLAGS=-Wall -L.

all: $(TARGETS)

clean:
	-rm -f *.o $(TARGETS) lib*.*

main.o: main.c socket.h
	$(CC) $(CFLAGS) -c $<
socket.o: socket.c socket.h
	$(CC) $(CFLAGS) -c $<

run:
	cp ./run_script ./run
	chmod +x run
	@echo To start server, type ./run [port]

# this is the static library, we use ar to build it
#lib_static.a: socket.o
#	ar rcv $@ $^

# SHARED LIB
# all of the objects must be compiled -fpic

lib_shared.so: socket.o
	$(CC) -shared -o $@ $^

# here is the socket program built all three ways
#socket: main.o socket.o
#	$(CC) $(LDFLAGS) $^ -o $@

#test_static: main.o lib_static.a
#	$(CC) $(LDFLAGS) $^ -o $@ -l_static

socket_shared: main.o lib_shared.so
	$(CC) $(LDFLAGS) $< -o $@ -l_shared

