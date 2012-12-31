
/*
 *  * sample code for file descriptor I/O
 *   * done in class
 *    * Thu Sep 15
 *     */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// close
#include <unistd.h>


int main()
{
    char buf[256];
    int rc;
    int fd = open( "file", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR );
   
    strcpy ( buf, "this is a test\n" );
    printf ( "buf ='%s'\n", buf );
    rc = write( fd, buf, strlen ( buf ) );
    printf ( "bytes sent = %d\n", rc );

                            
    strcpy ( buf, "just another test\n" );
    printf ( "buf ='%s'\n", buf );
    rc = write( fd, buf, strlen ( buf ) );
    printf ( "bytes sent = %d\n", rc );

    close(fd);

    
    fd = open( "file", O_RDWR );
    rc = read( fd, buf, 20 );
    buf[ rc ] = '\0';
    printf ( "bytes read = %d\n", rc);
    printf ( "buf ='%s'\n",buf );
    
    close(fd);
    return 0;
}
