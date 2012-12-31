#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

#include"socket.h"

#define SIZE      256
#define TCP       6
#define QUEUESIZE 10
#define ERROR     -1

char* parse(const char*);

// int  fdprintf(   const int, const char*, ...);
// int  fdgets(     char*,     int,         const int);
// void server_init(TCP_Server*, const int);
