
CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall


libqueue.a:queue.o
       ar rcv $@ $^

queue.o: queue.c queue.h

clean:
       -rm -f *.o *.a
