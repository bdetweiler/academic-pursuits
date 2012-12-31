TARGETS=lib_shared.so
CC=gcc
CFLAGS=-Wall -I. -fpic
LDFLAGS=-Wall -L.
SFLAGS=-warnposix

all: $(TARGETS)

# here is the socket program built all three ways
#socket_shared: lib_shared.so
#	$(CC) $(LDFLAGS) $< -o $@ -l_shared

# SHARED LIB
# all of the objects must be compiled -fpic
lib_shared.so: socket.o
	$(CC) -shared -o $@ $^

socket.o: socket.c socket.h
	$(CC) $(CFLAGS) -c $<

splint:
	splint $(SFLAGS) socket.c

clean:
	-rm -f *.o $(TARGETS) lib*.*
