
/*
 * John W. Clark
 * program to generate random numbers
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main( int argc, char ** argv )
{
    int min, max, num;
    int i;
    if ( argc < 4 )
    {
        fprintf( stderr, "Usage : %s min max number\n", argv[0] );
        fprintf( stderr, "ex : %s 0 100 20\n", argv[0] );
        fprintf( stderr, " generates 20 numbers between 0 and 100\n" );
        exit(1);
    }
    min = atoi( argv[1] );
    max = atoi( argv[2] );
    num = atoi( argv[3] );
    srand( time ( 0 ) );

    for( i = 0 ; i < num ; ++i )
    {
        printf( "%d ", ( rand() % ( max - min + 1 )) + min );
    }
    printf( "\n" );

    return 0;
}

