
#include<stdlib.h>
#include"stack.h"

void init ( STACK * s )
{
    s->size = 10;
    s->arr = ( int * ) malloc( s->size * sizeof( int ) );
    s->top = 0;
}

void push( STACK * s , const int foo )
{
    if ( s->top >= s->size )
    {
        s->size += 10;
        s->arr = ( int * ) realloc( s->arr, s->size * sizeof( int ) );
    }
    s->arr[ (s->top)++ ] = foo;
}

int pop( STACK * s )
{
    int rval = 0;
    if ( empty(s) )
    {
        printf( "pop error!" );
    }
    else
    {
        rval = s->arr[ --(s->top) ];
    }
    return rval;
}

int peek( STACK * s )
{
    int rval = 0;
    if ( empty(s) )
    {
        printf( "peek error!" );
    }
    else
    {
        rval = s->arr[ s->top - 1 ];
    }
    return rval;
}

int empty( STACK * s )
{
    return ( (s->top) <= 0 );
}


