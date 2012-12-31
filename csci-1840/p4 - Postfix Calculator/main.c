#include<stdio.h>
#include<stdlib.h>

#include"stack.h"

int main(void)
{
    float i = 0.0;
    Stack s;
    stack_init(&s);

    for(i = 0.0; i <= 24; ++i)
    {
        printf("Push it! %f\n", i);
        s.push(&s, i);
        printf("PEEK A BOO! %f\n", s.peek(&s));
    }

    while(!s.empty(&s))
    {
        printf("%f\n", s.pop(&s));
    }
    
    return 0;
}
