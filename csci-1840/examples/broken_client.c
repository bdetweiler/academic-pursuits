
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
    struct hostent * h;
    struct sockaddr_in server;
    struct sockaddr_in client;
    //socklen_t cli_len = sizeof( client );
    int rc;
    int sd;
    char buf[SIZE];

    if ( argc < 3 )
    {
        printf ( "usage: %s hostname port_num\n", argv[0] );
        exit(1);
    }
    // argv[1] is the hostname
    h = gethostbyname( argv[1] );
    port_num = atoi( argv[2] );

    p = getprotobyname ( "tcp" );
    proto_num = p->p_proto;
    sd = socket ( AF_INET, SOCK_STREAM, proto_num );
    if ( sd < 0 )
    {
        fprintf( stderr, "cannot open socket!\n" );
        exit(1);
    }

#if 0
    // bind to the local info
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = htonl ( INADDR_ANY );
    client.sin_port = htons ( port_num );

    rc = bind ( sd, (struct sockaddr *) &client, sizeof(client) );
    if ( rc < 0 )
    {
        fprintf( stderr, "cannot bind port!\n" );
        exit(1);
    }
#endif

    // we need to give the server address
    // come from hostent
    // MISSING SOMETHING HERE
    server.sin_family = AF_INET;
    memcpy( (void*)server.sin_addr.s_addr ,
            (void*)h->h_addr , h->h_length );
    server.sin_port = htons ( port_num );

    /* TODO connect */
    rc = connect( sd, (struct sockaddr *)&server, sizeof(server) );
    if ( rc )
    {
        printf ( "connect failed!\n" );
        exit(1);
    }

    rc = read( sd, buf, SIZE-1 );
    if ( rc <= 0 )
    {
        printf ( "read failed!\n" );
        close(sd);
        exit(1);
    }
    else
    {
        buf[ rc ] = '\0';
        printf ( "read %d bytes '%s'\n", rc, buf );
        close(sd);
    }

    return 0;
}
