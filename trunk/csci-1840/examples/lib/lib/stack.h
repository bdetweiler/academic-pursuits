#include<stdio.h>


typedef struct stack_st
{
    int * arr;
    int size;
    int top;
} STACK ;

void init ( STACK * s );
void push( STACK * , const int );
int pop( STACK * );
int peek( STACK * );
int empty( STACK * );
