typedef struct stack
{
    char** arr;
    int size;
    int top;

    const char* (*peek)(struct stack*);
    void (*push)(struct stack*, const char*);
    void (*print)(struct stack*);
    char* (*pop)(struct stack*);
    char* (*pop_bottom)(struct stack*);
    const char* (*peek_bottom)(struct stack*);

}Stack;

void init_stack(Stack*);
void free_stack(Stack*);

int stack_empty(Stack*);

void stack_print(Stack*);
const char* stack_peek(Stack*);
void stack_push(Stack*, const char*);
char* stack_pop(Stack*);
char* stack_pop_bottom(Stack*);
const char* stack_peek_bottom(Stack*);

#define SNUM 10
