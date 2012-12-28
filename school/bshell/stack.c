#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"stack.h"


void init_stack(Stack* s)
{
    s->size = SNUM;
    s->arr = (char**)malloc(s->size * sizeof(char**));
    s->top = 0;

    s->peek = stack_peek;
    s->print = stack_print;
    s->pop = stack_pop;
    s->pop_bottom = stack_pop_bottom;
    s->peek_bottom = stack_peek_bottom;
    s->push = stack_push;
}

void free_stack(Stack* s)
{
    int i = 1;
    for(; i < s->top; ++i)
        if(s->arr[i])
            free(s->arr[i]);

    if(s->arr)
        free(s->arr);
}

const char* stack_peek(Stack* s)
{
    return s->arr[s->top];
}


void stack_print(Stack* s)
{
    unsigned int i = s->top;
    printf("TOP: %d\n", s->top);
    for(; i > 0; --i)
        printf("%d: %s\n", i, s->arr[i]);
    printf("BOTTOM: %d\n", i);
}

const char* stack_peek_bottom(Stack* s)
{
    return s->arr[1];
}

void stack_push(Stack* s, const char* item)
{

    //  if full 
    if(s->top >= s->size)
    {
        s->arr = (char**)realloc(s->arr, (s->size + SNUM) * sizeof(char**));
        s->size = s->size + SNUM;
    }

    s->arr[++(s->top)] = (char*)malloc(strlen(item) * sizeof(char*));

    strncpy(s->arr[s->top], item, strlen(item));
    s->arr[s->top][strlen(item)] = '\0'; 
}

char* stack_pop(Stack* s)
{
    static char* rval = NULL;

    if(!s->top)
    {
        fprintf(stderr, "pop error!\n");
        exit(1);
    }

    rval = s->arr[(s->top)--];
    return rval;
}

// I call this stack-plus-plus
// We can yank the bottom out of it and get the data as if it were
// a queue. So, it's not quite a linked list, but sort of. Whatever.
char* stack_pop_bottom(Stack* s)
{
    static char* rval = NULL;

    int   nsize = s->size - 1;
    char** narr  = (char**)malloc(nsize * sizeof(char**));
    unsigned int i = 2;

    if(!s->top)
    {
        fprintf(stderr, "dequeue error!\n");
        exit(1);
    }

    if(s->top > 0)
    {
        rval = (char*)malloc(strlen(s->arr[1]) * sizeof(char*));
        strncpy(rval, s->arr[1], strlen(s->arr[1]));
        rval[strlen(s->arr[1])] = '\0';
    }

    if(s->top > 1)
        for(i = 2; i <= s->top; ++i)
        {
            narr[i - 1] = (char*)malloc(strlen(s->arr[i]) * sizeof(char*));
            strncpy(narr[i - 1], s->arr[i], strlen(s->arr[i]));
            narr[i - 1][strlen(s->arr[i])] = '\0';
        }
    else
    {
        narr[0] = NULL;

        if(s->arr[1])
            free(s->arr[1]);
    }

    for(i = 1; i < s->top; ++i)
        if(s->arr[i])
            free(s->arr[i]);

    if(s->arr)
        free(s->arr);


    --(s->top);
    s->arr = narr;
    s->size = nsize;

    return rval;
}




