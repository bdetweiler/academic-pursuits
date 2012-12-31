/******************************************************************************
 * Filename: stack.h                                                          *
 * Author:   Brian Detweiler                                                  *
 * Notes:    This header file contains the implementation of the stack as     *
 *           well. It is templated so should work for any data type.          *
 *****************************************************************************/

#include<iostream>
using namespace std;

template<class X>
class Stack
{
    private:
        int size;
        X   *arr;
        int top;
        static const int SIZE = 10;
        // Need to put copy constructor here: operator =
    public:
        /* This is more efficient; Since we know the values
         * we are able to pass them right away */
        Stack(void) : size(SIZE), arr(new X[size]), top(-1) {}
        ~Stack(void) { delete [] arr; } 
        bool empty(void) const { return top < 0; }
        bool full(void) const {  return (top + 1) <= size; }
        void push(const X);
        X  pop(void);
        X  peek(void) const;
};

template<class X>
void Stack<X>::push(const X foo)
{
    if(full())
    {
        int nsize = size + SIZE;
        X *narr = new X[nsize];
        for(int i = 0; i < size; ++i)
            narr[i] = arr[i];
        delete [] arr;
        size = nsize;
        arr  = narr;
    }
    arr[++top] = foo;

}

template<class X>
X Stack<X>::pop(void)
{
    X rval = 0;
    if(empty())
        cerr << "error in " << __PRETTY_FUNCTION__ << endl;
    else
        rval = arr[top--];
    return rval;
}

template<class X>
X Stack<X>::peek(void) const
{
    X rval = 0;
    if(empty())
        cerr << "error in " << __PRETTY_FUNCTION__ << endl;
    else
        rval = arr[top];
    return rval;
}



