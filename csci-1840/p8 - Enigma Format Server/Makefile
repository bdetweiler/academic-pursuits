TARGETS=enigma socket
#libshared.so
CC=gcc
CFLAGS=-Wall -I. -fpic
LDFLAGS=-Wall -L.

all: $(TARGETS)
clean:
	rm -f *.o $(TARGETS)
	make --directory=eformatsvr/ clean	

# to use the implicit linking the root of the target
# MUST match the first dependancy

# SHARED LIB
# all of the objects must be compiled -fpic
#lib_shared.so: socket.o
#	$(CC) -shared -o $@ $^

#socket.o: socket.c socket.h
#	$(CC) $(CFLAGS) -c $<


enigma:      enigma.o    spindle.o stecker.o reflector.o rotor.o socket.o
enigma.o:    enigma.c    spindle.o 
spindle.o:   spindle.c   spindle.h stecker.h reflector.h rotor.h 
stecker.o:   stecker.c   stecker.h
reflector.o: reflector.c reflector.h 
rotor.o:     rotor.c     rotor.h
# socket.o:    socket.c	 socket.h

socket:
	make --directory=eformatsvr/

