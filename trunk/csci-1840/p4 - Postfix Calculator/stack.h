#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<assert.h>

typedef struct stack
{
    // function pointers to our class "methods"
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
    int    count;
} Stack;

// Constructor
void  stack_init( Stack*);

// Methods
void  stack_free( Stack*);
int   stack_empty(Stack*);
int   stack_full( Stack*);
void  stack_push( Stack*, const float);
float stack_pop(  Stack*);
float stack_peek( Stack*);

#define SNUM 5
