TARGETS=libsocket.so server client run
CC=gcc
CFLAGS=-Wall -I. -fpic
LDFLAGS=-Wall -L.

all: $(TARGETS)

############ LIBRARY ################
libsocket.so: socket.o
	$(CC) -shared -o $@ $^
socket.o: socket.c socket.h
	$(CC) $(CFLAGS) -c $<

########### SERVER ################
server:	server.o 
	$(CC) $(LDFLAGS) -lsocket $< -o $@ 
server.o: server.c server.h 
	$(CC) $(LDFLAGS) -c $<

########### CLIENT ################
client: client.o 
	$(CC) $(LDFLAGS) -lsocket $< -o $@ 
client.o: client.c client.h 
	$(CC) $(LDFLAGS) -c $<

run:
	@cp ./run_script_client ./run_client
	@cp ./run_script_server ./run_server
	@chmod +x run_client run_server
	@echo -e "\n"

splint:
	splint -warnposix socket.c socket.h server.c server.h client.c client.h

clean:
	-rm -f *.o $(TARGETS) lib*.* run_client run_server


