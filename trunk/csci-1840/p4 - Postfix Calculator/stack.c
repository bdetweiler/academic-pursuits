/*
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<ctype.h>
#include<math.h>
*/
#include"stack.h"

/*
 
typedef struct stack
{
    // function pointers 
    void  (*free)(  struct stack * );
    int   (*empty)( struct stack * );
    int   (*full)(  struct stack * );
    void  (*push)(  struct stack *, const float );
    float (*pop)(   struct stack * );
    float (*peek)(  struct stack * );

    // data elements for storage
    float* arr;
    int    size;
    int    top;
} Stack;

void  stack_init( Stack*);
void  stack_free( Stack*);
int   stack_empty(Stack*);
int   stack_full( Stack*);
void  stack_push( Stack*, const float);
float stack_pop(  Stack*);
float stack_peek( Stack*);

#define SNUM 5
*/

void stack_init(Stack* s)
{
    s->size = SNUM;
    s->arr  = malloc(sizeof(float) * s->size);
    assert(s->arr);
    s->top  = 0;

    // Function pointers:
    s->free    = stack_free;
    s->empty   = stack_empty;
    s->full    = stack_full;
    s->push    = stack_push;
    s->pop     = stack_pop;
    s->peek    = stack_peek;
}

void stack_free(Stack* s)
{
    free(s->arr);
}

int stack_empty(Stack* s)
{
    int rval = 0;
    if(s->top <= 0)
        rval = 1;

    return rval;
}

int stack_full(Stack* s)
{
    return(s->top >= s->size);
}

void stack_push(Stack* s, const float foo)
{
    // If full
    if(stack_full(s))    
    {
        int    nsize = s->size + SNUM;
        float* narr  = malloc(sizeof(int) * nsize);

        /* copy from the front of arr, to the 0 index in narr */
        memcpy(narr, s->arr + s->top,
                (s->size - s->top) * sizeof(int));
        /* copy the front elements from arr in the rest of narr */
        memcpy(narr + (s->size - s->top) , s->arr,
                s->top * sizeof(int));
        /* ToDo: Check this part. Not too sure, especially
         * about the s->top part.
         */
        free(s->arr);
        s->arr   = narr;
        s->size  = nsize;
        
        // WTF???
        // s->top   = s->count;
    }
    s->arr[(s->top)++] = foo;
    ++(s->count);
}

float stack_pop(Stack* s)
{
    float rval;
    if(stack_empty(s) != 0)
    {
        fprintf(stderr, "pop error!\n" );
        exit(EXIT_FAILURE);
    }
    rval = s->arr[--(s->top)];

    // Why do we do this step?
    s->top %= s->size;

    --(s->count);
    return rval;
}

float stack_peek(Stack* s)
{
    int rval;

    if(stack_empty(s) != 0)
    {
        fprintf(stderr, "pop error!\n" );
        exit(EXIT_FAILURE);
    }

    rval = s->arr[(s->top) - 1];

    // Why do we do this step?
    return rval;
}

