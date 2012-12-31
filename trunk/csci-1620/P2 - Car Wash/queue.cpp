#include <iostream>
using namespace std;
#include "queue.h"

/* Input:   none
 * Output:  none
 * Returns: none
 * Notes:   Default constructor
 */
Queue::Queue(void)
{
    back = 0;
    size = 5;
    arr  = new int[size];
}

/* Input:   none
 * Output:  none
 * Returns: none
 * Notes:   Destructor
 */
Queue::~Queue(void)
{
    delete [] arr;
}

/* Input:   none
 * Output:  none
 * Returns: A bool (empty or not)
 * Notes:   Tells if queue is empty or not
 */
bool Queue::empty(void) const
{
    return back <= 0;
}

/* Input:   none
 * Output:  none
 * Returns: A bool (full or not)
 * Notes:   Tells if queue is full or not
 */
bool Queue::full(void) const
{
    return back >= size;
}

/* Input:   none
 * Output:  none
 * Returns: An int
 * Notes:   Tells how many elements are in the queue
 */
int Queue::length(void) const
{
    return back + 1; // back starts at 0
}

/* Input:   An int
 * Output:  none
 * Returns: An int
 * Notes:   Enqueues an integer if the queue is not full
 */
void Queue::enqueue(const int foo)
{
    if(full())
    {
        // allocate more memory
        int nsize = size + 5;
        int *narr = new int[nsize];   // Segfault here if number is too big
        for(int i = 0; i < size; ++i)
        {
            narr[i] = arr[i];
        }
        delete [] arr;
        *arr  = *narr;
        size = nsize;
    }
    arr[back++] = foo; // put foo in the right place then increment it
}

/* Input:   none
 * Output:  none
 * Returns: A bool (full or not)
 * Notes:   Tells if queue is full or not
 */
int Queue::dequeue(void)
{
    if(empty())
    {
        cerr << "Queue is empty." << endl;
        exit(1);
    }
    int rval = arr[0];
    for(int i = 1; i < back; ++i)
    {
        arr[i-1] = arr[i];
    } 
    --back;
    return rval;
}


// todo: Assignment and copy constructor
