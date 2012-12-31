#include"socket.h"

// TCP 6
// QUEUESIZE 10
// ERROR -1


/*
 * tcp_error
 * --
 * Input:   const char*
 * Output:  None
 * Return:  None
 * Notes:   An error wrapper; This will save
 *          an extra line of code and formatting
 *          for each function. 
 *          TODO: Close connections?
 */
void tcp_error(const char* message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}


/*
 * tcp_sopen and tcp_copen
 * --
 * Input:   TCP_Server* and TCP_Client*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for open()
 */
void tcp_sopen(TCP_Server* s)
{
    s->sd = socket(AF_INET, 
                   SOCK_STREAM, 
                   s->proto_num);
    if(s->sd < 0)
        s->serror("cannot open socket!");
}
void tcp_copen(TCP_Client* c)
{
    c->sd = socket(AF_INET, 
                   SOCK_STREAM, 
                   c->proto_num);
    if(c->sd < 0)
        c->cerror("cannot open socket!");
} 

/*
 * tcp_sbind tcp_cbind
 * --
 * Input:   TCP_Server* and TCP_Client*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for bind()
 */
void tcp_sbind(TCP_Server* s)
{
    s->rc = bind(s->sd, 
                (struct sockaddr*) &(s->svr), 
                (socklen_t)sizeof(s->svr));
    if(s->rc < 0)
        s->serror("cannot bind port!");
}
void tcp_cbind(TCP_Client* c)
{
    c->rc = bind(c->sd, 
                (struct sockaddr*) &(c->cli), 
                (socklen_t)sizeof(c->cli));
    if(c->rc < 0)
        c->cerror("cannot bind port!");
}

/*
 * tcp_connect
 * --
 * Input:   TCP_Client*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for connect(); 
 *          This is only for the client
 */
#if 0
void tcp_connect(TCP_Client* c)
{
     c->rc = connect(c->sd, 
                    (struct sockaddr *)&c, 
                    sizeof(c));
     if(c->rc)
       c->cerror("connect failed!");
}
#endif

/*
 * tcp_listen
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for listen();
 *          This is for the server only
 */
void tcp_listen(TCP_Server* s)
{
    // rc queue 10 req.
    s->rc = listen(s->sd, QUEUESIZE);  
    if(s->rc < 0)
        s->serror("listen failed!");
}

/*
 * tcp_accept
 * --
 * Input:   TCP_Server*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for accept();
 *          This is for the server only
 */
void tcp_accept(TCP_Server* s)
{
    s->sd2 = accept(s->sd, 
                    (struct sockaddr*) &(s->cli), 
                    &(s->cli_len));
printf("server has accepted connection.\n");
    if(s->sd2 < 0)
        s->serror("accept failed!");
}

/*
 * tcp_sread and tcp_cread
 * --
 * Input:   TCP_Server* and TCP_Client*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for read()
 */
void tcp_sread(TCP_Server* s)
{
    ssize_t t;
    t = read(s->sd2, &(s->buf), BUFSIZ - 1);
    if(t < 0)
    {
        s->sclose(s, s->sd2);
        s->serror("read failed!");
    }
}
void tcp_cread(TCP_Client* c)
{
    ssize_t t;
    t = read(c->sd, &(c->buf), BUFSIZ - 1);
    if(t < 0)
    {
        c->cclose(c, c->sd);
        c->cerror("read failed!");
    }
}

/*
 * tcp_swrite, tcp_cwrite, 
 * --
 * Input:   TCP_Server* and TCP_Client*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for write()
 */
void tcp_swrite(TCP_Server* s)
{
    ssize_t t;
    t = write(s->sd2, &(s->buf), strlen(s->buf));
    if(t < 0)
        s->serror("write failed!");
    // Zero out buffer
    memset(&(s->buf), 0, BUFSIZ - 1);
}
void tcp_cwrite(TCP_Client* c)
{
    ssize_t t;
    t = write(c->sd, &(c->buf), strlen(c->buf));
    if(t < 0)
        c->cerror("write failed!");
    // Zero out buffer
    memset(&(c->buf), 0, BUFSIZ - 1);
}

/*
 * tcp_sclose
 * --
 * Input:   TCP_Server*, TCP_Client*, const int
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for close()
 *          Either s or c will be NULL. The function
 *          will use this to determine which one it
 *          should perform operations on. 
 */
void tcp_sclose(TCP_Server* s, const int sdx)
{
    if(sdx == s->sd)
        close(s->sd);
    else if(sdx == s->sd2)
        close(s->sd2);
    else
        s->serror("close failed!");
}
void tcp_cclose(TCP_Client* c, const int sdx)
{
    if(sdx == c->sd)
        close(c->sd);
    // free(c->h); // ???
    else if(sdx == c->sd2)
        close(c->sd2);
    else
        c->cerror("close failed!");
} 

/*
 * tcp_connect
 * --
 * Input:   TCP_Client*, struct sockaddr*
 * Output:  None
 * Return:  None
 * Notes:   Wrapper for connect()
 *
 */
void tcp_connect(TCP_Client* c, struct sockaddr* server)
{
    c->rc = connect(c->sd, 
                   (struct sockaddr *) server, 
                   sizeof(server));
    if(c->rc == 0)
        c->cerror("connect failed!");
} 


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
    // I don't think I need this
    s->cli_len             = sizeof(s->cli);
    s->p                   = getprotobynumber(TCP);
    s->proto_num           = s->p->p_proto;
    s->port_num            = port_num;
   
    s->svr.sin_family      = AF_INET;
    s->svr.sin_addr.s_addr = htonl(INADDR_ANY);
    s->svr.sin_port        = htons((uint16_t)port_num);

    // METHODS
    s->serror              = tcp_error;
    s->sopen               = tcp_sopen;
    s->sbind               = tcp_sbind;
    s->slisten             = tcp_listen;
    s->saccept             = tcp_accept;
    s->sread               = tcp_sread;
    s->swrite              = tcp_swrite;
    s->sclose              = tcp_sclose;
}

/*
 * client_init
 * --
 * Input:   TCP_Client*, const int
 * Output:  None
 * Return:  None
 * Notes:   This is our "constructor" for the
 *          TCP_Client
 */
void client_init(TCP_Client* c, 
                 const char* hostname, 
                 const int port_num)
{
    c->cli_len             = sizeof(c->cli);

    // Remember, p is a PROTOENT struct
    c->p                   = getprotobynumber(TCP);
    c->proto_num           = c->p->p_proto;
    c->port_num            = port_num;

    c->h                   = gethostbyname(hostname);

    c->cli.sin_family      = AF_INET;
    c->cli.sin_addr.s_addr = htonl(INADDR_ANY);
    c->cli.sin_port        = htons(0);

    c->svr.sin_family = AF_INET;

    /*
     * Wow, this is fugly.
     */
    memcpy((void*)&(c->svr.sin_addr.s_addr),
           (void*)c->h->h_addr_list[0], 
           c->h->h_length);
    c->svr.sin_port = htons((uint16_t)c->port_num);

    // METHODS
    c->cerror              = tcp_error;
    c->copen               = tcp_copen;
    c->cbind               = tcp_cbind;
    c->cconnect            = tcp_connect;
    c->cread               = tcp_cread;
    c->cwrite              = tcp_cwrite;
    c->cclose              = tcp_cclose;
}

