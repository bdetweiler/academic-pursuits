#include"socket.h"

// TCP 6
// QUEUESIZE 10
// ERROR -1

int tcp_server( const int server_port );
int tcp_accept( const int sd );
int tcp_client( const int server_port, const char * host, int * sd );

int fdprintf( const int fd, const char * fmt, ... );
int fdgets(char *s, int size, const int fd );

