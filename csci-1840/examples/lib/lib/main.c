#include<stdlib.h>
#include<stdio.h>
#include"stack.h"

int main()
{
    int i;
    STACK s;

    init( &s );
    for( i = 0 ; i < 10 ; ++i )
    {
        push( &s, i );
    }
    printf("peek %d\n", peek(&s) );

    for( i = 0 ; i < 5 ; ++i )
    {
        printf( "pop %d\n", pop(&s) );
    }
    printf("peek %d\n", peek(&s) );

    for( i = 15 ; i < 19 ; ++i )
    {
        push( &s, i );
    }
    printf("peek %d\n", peek(&s) );

    while( !empty( &s ) )
    {
        printf( "pop %d\n", pop(&s) );
    }
    printf("peek %d\n", peek(&s) );

    return 0;
}

