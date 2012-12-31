#ifndef MYSOCK_H
#define MYSOCK_H

#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define SIZE 256


#define TCP 6
#define QUEUESIZE 10
#define ERROR -1

typedef struct tcp_server
{
    // Data Members
    
    // PROTOCOL NUMBER
    int                proto_num;
    int                port_num;
    int                rc;
    struct protoent*   p;
    struct sockaddr_in svr;
    struct sockaddr_in cli;
    socklen_t          cli_len;
    
    // SOCKET DESCRIPTORS
    // this is set in tcp_open()
    int                sd;
    int                sd2;

    // Buffer to write to
    char               buf[BUFSIZ];

    // Methods
    void (*sopen)  (struct tcp_server*);
    void (*sbind)  (struct tcp_server*);
    void (*slisten)(struct tcp_server*);
    void (*saccept)(struct tcp_server*);
    void (*sread)  (struct tcp_server*);
    void (*swrite) (struct tcp_server*);
    void (*sclose) (struct tcp_server*, const int);

#if 0
    // Encapsulation function
    void (*srun)(   struct TCP_Server*);
#endif
    // int (*fdprintf)(  struct TCP_Server*, const int, 
                      // const char*, ...); 
    // int (*fdgets)(    struct TCP_Server*, char*, int, 
                      // const int);
}TCP_Server;

// int  tcp_accept( const int);
// int tcp_client(const int, const char*, int*);

// int  fdprintf(   const int, const char*, ...);
// int  fdgets(     char*,     int,         const int);
void server_init(TCP_Server*, const int);
static void tcp_open(   TCP_Server*);
static void tcp_bind(   TCP_Server*);
static void tcp_listen( TCP_Server*);
static void tcp_accept( TCP_Server*);
static void tcp_read(   TCP_Server* s);
static void tcp_write(  TCP_Server* s);
static void tcp_close(  TCP_Server*, const int);
#if 0
void tcp_run(    TCP_Server*);
#endif
#endif
