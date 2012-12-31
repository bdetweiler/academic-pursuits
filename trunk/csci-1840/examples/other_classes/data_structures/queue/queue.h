
typedef struct queue
{
    int size;
    int * arr;
    int front;
    int back;
    int count;
} Queue ;

void init_queue ( Queue * );
void free_queue ( Queue * );
int queue_empty ( Queue * );
void enqueue ( Queue *, const int );
int dequeue ( Queue * );

#define QNUM 10
