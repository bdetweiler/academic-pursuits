#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"socket.h"

#define SIZE      256
#define TCP       6
#define QUEUESIZE 10
#define ERROR     -1

// int  tcp_accept( const int);
// int tcp_client(const int, const char*, int*);

// int  fdprintf(   const int, const char*, ...);
// int  fdgets(     char*,     int,         const int);
// void server_init(TCP_Server*, const int);
