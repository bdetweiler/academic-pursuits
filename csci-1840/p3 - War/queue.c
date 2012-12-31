
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"queue.h"


void init_queue(Queue* q)
{
    q->size  = QNUM;
    q->arr   = malloc (sizeof(int) * q->size);
    q->front = 0;
    q->back  = 0;
    q->count = 0;
}

void free_queue(Queue* q)
{
    free(q->arr);
}

int queue_empty(Queue* q)
{
    return(q->count <= 0);
}


void enqueue ( Queue * q, const int foo )
{
    if ( q->count >= q->size )    /* if full */
    {
        int nsize = q->size + QNUM;
        int * narr = ( int * ) malloc ( sizeof ( int ) * nsize );

#if 0
        int i;
        for ( i = 0 ; i < q->size ; ++i )
            narr[i] = q->arr[ ( q->front + i ) % q->size ];
#else
        /* copy from the front of arr, to the 0 index in narr */
        memcpy( narr, q->arr + q->front,
                ( q->size - q->front ) * sizeof ( int ) );
        /* copy the front elements from arr in the rest of narr */
        memcpy( narr + ( q->size - q->front ) , q->arr,
                q->front * sizeof ( int ));
#endif
        free ( q->arr );
        q->arr = narr;
        q->size = nsize;
        q->front = 0;
        q->back = q->count;
    }
    q->arr[ (q->back)++ ] = foo;
    q->back %= q->size;
    ++(q->count);
}

int dequeue ( Queue * q )
{
    int rval;
    if ( queue_empty( q ) )
    {
        fprintf ( stderr, "dequeue error!\n" );
        exit( 1 );
    }
    rval = q->arr[ (q->front)++ ];
    q->front %= q->size;
    --(q->count);
    return rval;
}





