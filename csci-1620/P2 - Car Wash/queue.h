#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
    private:
        int back;
        int size;
        int *arr;
    public:
        Queue(void);
        ~Queue(void);
        void enqueue(const int);
        int  dequeue(void);
        int  length(void) const;
        bool empty(void)  const;
        bool full(void)   const;
};

#endif
