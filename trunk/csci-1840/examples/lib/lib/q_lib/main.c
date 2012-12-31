
#include<stdio.h>
#include<queue.h>


int main()
{
    Queue q;
    int i;

    init_queue( &q );

    for ( i = 0 ; i < 10 ; ++i )
        enqueue( &q, i );

    for ( i = 0 ; i < 5 ; ++i )
        printf ( "%d ", dequeue( &q ) );
    printf ( "\n");

    for ( i = 0 ; i < 20 ; ++i )
        enqueue( &q, i + 10 );

    while ( !queue_empty( &q ) )
        printf ( "%d ", dequeue( &q ) );
    printf ( "\n");


    free_queue( &q );

    return 0;
}


