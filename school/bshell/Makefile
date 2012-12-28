CC=gcc-4.1
LDFLAGS=-Wall -L.
CFLAGS=-Wall -I. -fpic
#CXXFLAGS=-Wall
LIBFLAGS=-W -Wall -ansi -pedantic -O2
#USELIBFLAGS=-W -Wall -ansi -pedantic -O2 -L"."
TARGETS=clean clear bshell kbhit

all: ${TARGETS}

clear:
	clear
#bshell:  bshell.o
#	$(CC) $(LDFLAGS) bshell.o -o bshell
bshell: bshell.o history.o command.o path.o stack.o libkbhit.a
	$(CC) $(LDFLAGS) $^ -o $@  -lkbhit

bshell.o: bshell.c kbhit.h
	$(CC) $(CFLAGS) -c $<

history.o: history.c history.h
	$(CC) $(CFLAGS) -c $<

command.o: command.c command.h
	$(CC) $(CFLAGS) -c $<

path.o: path.c path.h
	$(CC) $(CFLAGS) -c $<

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $<

kbhit.o: kbhit.c kbhit.h
	$(CC) $(CFLAGS) -c $<

kbhit: kbhit.c
	$(CC) $(LIBFLAGS) -c -o libkbhit.a kbhit.c

# this is the static library, we use ar to build it
libkbhit.a: kbhit.o
	ar rcv $@ $^


# UNIT TESTING
history_test: history_test.o history.o
	$(CC) $(LDFLAGS) $^ -o $@
history_test.o: history_test.c history.h
	$(CC) $(CFLAGS) -c $<

path_test: path_test.o path_test.o path.o stack.o
	$(CC) $(LDFLAGS) $^ -o $@
path_test.o: path_test.c path.h stack.h
	$(CC) $(CFLAGS) -c $<

command_test: command_test.o command_test.o command.o 
	$(CC) $(LDFLAGS) $^ -o $@
command_test.o: command_test.c command.h
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f *.o $(TARGETS) history_test lib*.*

