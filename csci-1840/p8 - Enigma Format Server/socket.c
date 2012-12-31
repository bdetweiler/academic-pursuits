#include"socket.h"

// TCP 6
// QUEUESIZE 10
// ERROR -1

/*
 * server_init
 * --
 * Input:   TCP_Server*, const int
 * Output:  None
 * Return:  None
 * Notes:   This is our "constructor" for the 
 *          TCP_Server
 */
void server_init(TCP_Server* s, const int port_num)
{
    s->cli_len             = (socklen_t)sizeof(s->cli);

    // Remember, p is a struct
    free(s->p);
    s->p                   = getprotobynumber(TCP);
    s->proto_num           = s->p->p_proto;
    s->port_num            = port_num;
   
    s->svr.sin_family      = AF_INET;
    s->svr.sin_addr.s_addr = htonl(INADDR_ANY);
    s->svr.sin_port        = htons((uint16_t)port_num);

    // METHODS
    s->sopen               = tcp_open;
    s->sbind               = tcp_bind;
    s->slisten             = tcp_listen;
    s->saccept             = tcp_accept;
    s->sread               = tcp_read;
    s->swrite              = tcp_write;
    s->sclose              = tcp_close;
}

/*
 * tcp_open
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for open()
 */
void tcp_open(TCP_Server* s)
{
    s->sd = socket(AF_INET, SOCK_STREAM, 
                   s->proto_num);
    if(s->sd < 0)
    {
        fprintf( stderr, "cannot open socket!\n");
        exit(EXIT_FAILURE);
    }
} 

/*
 * tcp_bind
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for bind()
 */
void tcp_bind(TCP_Server* s)
{
    s->rc = bind(s->sd, (struct sockaddr*) &(s->svr), 
                 (socklen_t)sizeof(s->svr));
    if(s->rc < 0)
    {
        fprintf( stderr, "cannot bind port!\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * tcp_listen
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for listen()
 */
void tcp_listen(TCP_Server* s)
{
    // rc queue 10 req.
    s->rc = listen(s->sd, QUEUESIZE);  
    if(s->rc < 0)
    {
        fprintf(stderr, "listen failed!\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * tcp_accept
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for accept()
 */
void tcp_accept(TCP_Server* s)
{
    s->sd2 = accept(s->sd, (struct sockaddr*) 
                    &(s->cli), &(s->cli_len));
    if(s->sd2 < 0)
    {
        fprintf(stderr, "accept failed!\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * tcp_read
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for read()
 */
void tcp_read(TCP_Server* s)
{
    ssize_t t;
    t = read(s->sd2, &(s->buf), BUFSIZ - 1);
    if(t < 0)
    {
        fprintf(stderr, "read failed!\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * tcp_write
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for write()
 */
void tcp_write(TCP_Server* s)
{
    ssize_t t;
    t = write(s->sd2, &(s->buf), strlen(s->buf));
    if(t < 0)
    {
        fprintf(stderr, "read failed!\n");
        exit(EXIT_FAILURE);
    }
    
    // Zero out buffer
    memset(&(s->buf), 0, BUFSIZ - 1);
}

/*
 * tcp_close
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for close()
 */
void tcp_close(TCP_Server* s, const int sdx)
{
    if(sdx == s->sd)
        (void)close(s->sd);
    else if(sdx == s->sd2)
        (void)close(s->sd2);
    else
    {
        fprintf(stderr, "close failed!\n");
        exit(EXIT_FAILURE);
    }
} 
