#include"client.h"

int main(int argc, char** argv)
{
    TCP_Client c;

    if(argc < 3)
    {
        printf("usage: %s hostname port_num\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    client_init(&c, argv[1], atoi(argv[2]));
    c.copen(&c);
    c.cbind(&c); 
    
    fgets(c.buf, BUFSIZ - 1, stdin);
    /*
     * Take Input
     */
    
    /* 
     * Connect to the server.
     */
    c.cconnect(&c, (struct sockaddr*) &(c.svr));
    /* 
     * Now do I/O
     */
    c.cwrite(&c);
    c.cread(&c);
    c.cclose(&c, c.sd);
    printf("%s", c.buf);
    return 0;
}
