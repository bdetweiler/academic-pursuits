
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 256


int main( int argc, char * argv[] )
{
    int port_num;
    int proto_num;
    struct protoent * p;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t cli_len = sizeof( client );
    int rc;
    int sd, sd2;
    char buf[SIZE];

    if ( argc < 2 )
    {
        printf ( "usage: %s port_num\n", argv[0] );
        exit(1);
    }
    port_num = atoi( argv[1] );

    p = getprotobyname ( "tcp" );
    proto_num = p->p_proto;
    sd = socket ( AF_INET, SOCK_STREAM, proto_num );
    if ( sd < 0 )
    {
        fprintf( stderr, "cannot open socket!\n" );
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl ( INADDR_ANY );
    server.sin_port = htons ( port_num );

    rc = bind ( sd, (struct sockaddr *) &server, sizeof(server) );
    if ( rc < 0 )
    {
        fprintf( stderr, "cannot bind port!\n" );
        exit(1);
    }

    rc = listen ( sd, 10 );  // queue 10 req.
    if ( rc < 0 )
    {
        fprintf( stderr, "listen failed!\n" );
        exit(1);
    }

    printf ( "waiting for a connection on port %d\n", port_num );

    sd2 = accept( sd, (struct sockaddr *) &client, &cli_len );
    if ( sd2 < 0 )
    {
        fprintf( stderr, "accept failed!\n" );
        exit(1);
    }

    sprintf ( buf, "hello from %s running on port %d\n",
            argv[0], port_num );

    rc = write ( sd2, buf, strlen( buf ) + 1 );
    if ( rc < 0 )
    {
        fprintf( stderr, "write failed!\n" );
        exit(1);
    }

    close(sd2);
    close(sd);


    return 0;
}



