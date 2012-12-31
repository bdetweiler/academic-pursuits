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

    /*
     * This should not go out of scope. It is inside
     * our struct, and as long as the struct is in
     * scope, this should be in scope.
     */
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
    void (*serror) (const char*);
    /*
     * TODO: It does not yet know what a struct tcp_client 
     *       is, so we need to fix this somehow.
     */
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

typedef struct tcp_client
{
    /*
     * PROTOCOL NUMBER
     */
    int                proto_num;
    int                port_num;
    int                rc;
    struct protoent*   p;
    struct hostent*    h;

    /*
     * This should not go out of scope. It is inside
     * our struct, and as long as the struct is in
     * scope, this should be in scope.
     */
    struct sockaddr_in cli;
    struct sockaddr_in svr;
    socklen_t          cli_len;

    // SOCKET DESCRIPTORS
    // this is set in tcp_open()
    int                sd;
    int                sd2;

    // Buffer to write to
    char               buf[BUFSIZ];

    // Methods
    void (*cerror)  (const char*);
    void (*copen)   (struct tcp_client*);
    void (*cbind)   (struct tcp_client*);
    void (*cconnect)(struct tcp_client*, struct sockaddr*);
    void (*cread)   (struct tcp_client*);
    void (*cwrite)  (struct tcp_client*);
    void (*cclose)  (struct tcp_client*, const int);
                     

    // int (*fdprintf)(  struct TCP_Server*, const int,
                      // const char*, ...);
    // int (*fdgets)(    struct TCP_Server*, char*, int,
                      // const int);
}TCP_Client;

// int  tcp_accept( const int);
// int tcp_client(const int, const char*, int*);

// int  fdprintf(   const int, const char*, ...);
// int  fdgets(     char*,     int,         const int);
void client_init(TCP_Client*, const char*, const int);
void server_init(TCP_Server*, const int);

void tcp_error(  const char*);
void tcp_sopen(  TCP_Server*);
void tcp_copen(  TCP_Client*);
void tcp_sbind(  TCP_Server*);
void tcp_cbind(  TCP_Client*);
void tcp_listen( TCP_Server*);
void tcp_accept( TCP_Server*);
void tcp_connect(TCP_Client*, struct sockaddr*);
void tcp_sread(  TCP_Server*);
void tcp_cread(  TCP_Client*);
void tcp_swrite( TCP_Server*);
void tcp_cwrite( TCP_Client*);
void tcp_sclose( TCP_Server*, const int);
void tcp_cclose( TCP_Client*, const int);
#endif
