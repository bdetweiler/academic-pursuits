/****************************************************************************
 * File:    dheap.cpp                                                       *
 * Author:  Brian Detweiler                                                 *
 * Use:     A d-Heap keeps either the largest or smallest element on the    *
 *          top so that remove() is O(1).                                   *
 ***************************************************************************/


#include<vector>
#include<iostream>
using namespace std;

// Macros for the parent, and left-most and right-most 
// children of the current node
#define par(x) (((x) - 1)/this->d)
#define left(x) ((this->d*(x))+1)
#define right(x) ((this->d*(x))+this->d)

typedef unsigned int u_int;
// Templated Heap class
template<class X>
class Heap
{
    private:
        vector<X> arr; 
        // d holds the value for how many children each parent has.
        u_int d; 
        // This tells us whether it is a min or max heap
        // A min heap will have the smallest number at the root
        // A max heap will have the largest number at the root
        bool min_heap;
        
        void reheapify();
        void percolateDown(u_int);
        void percolateUp(u_int);
    public:
        Heap(void) : d(2), min_heap(true) {;;;}
        // TODO:
        // Heap(const vector<X>); // Make a heap from a vector
        // Heap(const int*); // Make a heap from an array
        Heap(Heap&);
        ~Heap(void);
        // TODO:
        // Heap & operator = (Heap &);
        const int getD(void);
        const bool isMinHeap(void);

        void setD(const int);
        void setMinHeap(const bool);
        vector<X> getVect(void);
        X getElementAt(const u_int);
        int size(void);
        void insert(X);
        X remove(u_int foo);
        X getRoot(void) const;
        void merge(Heap<X> &);
        bool empty(void) const;
        int minChild(int);
        int maxChild(int);

        X remove_root(void);
        void print(void) const;
};

/*
 * Copy constructor
 * time: O(1)
 */
template<class X>
Heap<X>::Heap(Heap &foo)
{
    this->arr = foo.getVect();
    this->d = foo.getD();
    this->min_heap = foo.isMinHeap();
}

/*
 * Destructor
 * time: O(1)
 */
template<class X>
Heap<X>::~Heap(void)
{
    this->arr.clear();
    this->d = 0;
    this->min_heap = false;
}

/*
 * Grab the vector and return it.
 * time: O(1)
 */
template<class X>
vector<X> Heap<X>::getVect(void)
{
    return arr;
}

/*
 * Grab an element at a certain position in the vector
 * (Basically, a public way to view the vector)
 * time: O(1)
 */
template<class X>
X Heap<X>::getElementAt(const u_int foo)
{
    X rval;

    if(foo < arr.size())
        rval = arr[foo];
    else
        cerr << "No such element!" << endl;

    return rval;
}

/*
 * Grab the number of nodes and return it.
 * time: O(1)
 */
template<class X>
int Heap<X>::size(void)
{
    return arr.size();
}

/*
 * Return the d part of the heap
 * time: O(1)
 */
template<class X>
const int Heap<X>::getD(void)
{
    return this->d;
}

/*
 * Return if it is min heap or not
 * time: O(1)
 */
template<class X>
const bool Heap<X>::isMinHeap(void)
{
    return this->min_heap;
}

/*
 * Set the d of the heap 
 * (how many children per node)
 * time: O(1)
 */
template<class X>
void Heap<X>::setD(const int foo)
{
    if(foo >= 2)
        this->d = foo;
    else
    {
        cerr << "If you can't use a d-heap correctly, " 
             << "don't use one at all. Valid d values "
             << "are integers >= 2." 
             << endl;
        exit(1);
    }
}

/*
 * Set the min_heap part of the heap
 * setting the min_heap value
 *      time: O(1)
 * reheapifying
 *      time: O(log(n))
 */
template<class X>
void Heap<X>::setMinHeap(const bool foo)
{
    if(this->min_heap != foo)
    {
        this->min_heap = foo;
        // Since we are changing the type of heap,
        // we also need to reorginze the heap
        // time: O(log n)
        reheapify();
    }
}

/*
 * Find out if the heap is empty or not
 * time: O(1)
 */
template<class X>
bool Heap<X>::empty(void) const
{
    return arr.empty();
}

/*
 * Reorganizes a disorganized heap and restores
 * the heap property
 * time: O(log(n))
 */
template<class X>
void Heap<X>::reheapify(void)
{
    vector<X> arr_cpy = arr; 
    arr.clear();
    while(!arr_cpy.empty())
    {
        insert(arr_cpy.back());
        arr_cpy.pop_back();
    }
}
/*
 * Insert an element into the heap
 * time: O(log(n))
 */
template<class X>
void Heap<X>::insert(X foo)
{ 
    arr.push_back(foo);
    percolateUp(arr.size() - 1);
}

/*
 * Remove an element from the heap
 * time: O(log(n))
 */
template<class X>
X Heap<X>::remove(u_int foo = 0)
{
    if(foo >= arr.size())
    {
        cerr << "Error: Tried to remove non-existant element." << endl;
        exit(1);
    }

    // Get the value we are popping.
    X rval = arr[foo];
    // Pull the last element to plug the hole
    X move_me = arr.back();
    arr.pop_back();
    // Do a check to see if there was only one element left
    if(!arr.empty())
    {
        // Plug the hole!
        arr[foo] = move_me;
        // Percolate down starting at the newly plugged hole
        percolateDown(foo);
    }

    return rval;
}

/* 
 * Return the min child of the current node
 * time: O(d)
 */
template<class X>
int Heap<X>::minChild(int foo) 
{
    int minChild = 0;

    // If the left child is less than the size of the array,
    // find the minimum child of "foo"
	if(left(foo) <= arr.size()) 
    {
        // For right now, all we know is the left child is the min child,
        // until we find out differntly
        minChild = left(foo);
        // i = the left child of foo
        // While it is less than or equal to the right child of foo
        // && while it is less than the size of the array
	    for(u_int i = minChild + 1; i <= right(foo) && i < arr.size(); ++i) 
        {
            // If the value at i is less than the value at the previously
            // assigned minChild
            // FIXME: Need to add an isPtr() function to detect if X is a
            //        a pointer or not. Then we know whether or not to
            //        dereference it.
		    if(*arr[i] < *arr[minChild]) 
                // Reassign the minChild
                minChild = i;
        }
    }
    // Now we have the location of the minChild of foo
	return minChild;
}

/* 
 * Return the max child of the current node
 * time: O(d)
 */
template<class X>
int Heap<X>::maxChild(int foo) 
{
    int maxChild = 0;

	if(left(foo) <= arr.size()) 
    {
        maxChild = left(foo);
	    for(u_int i = maxChild + 1; i <= right(foo) && i <= arr.size(); ++i) 
		    if(*arr[i] > *arr[maxChild]) 
                maxChild = i;
    }
	return maxChild;
}

/* 
 * Return the extreme value which is at the root node
 * time: O(1)
 */
template<class X>
X Heap<X>::remove_root(void)
{
    return remove(0);
}

/*
 * Print the heap's contents
 * time: O(n)
 */
template<class X>
void Heap<X>::print(void) const
{
    // NOTE: Have to add an extra dereferencer to i to print pointers
    for(typename vector<X>::const_iterator i = arr.begin(); i != arr.end(); ++i)
        cout << **i << ' ';
    cout << endl;
}

/*
 * Returns the root of the heap
 * time: O(1)
 */
template<class X>
X Heap<X>::getRoot(void) const
{
    return arr.front();
}

/*
 * Merges one heap into another
 * time: O(log(n))
 */
template<class X>
void Heap<X>::merge(Heap<X> &foo)
{
    Heap<X> bar = foo;

    while(!bar.empty())
    {
        insert(bar.remove_root());
    }
}

/*
 * Percolate an element down from a heap or sub-heap
 * time: O(d)
 */
template<class X>
void Heap<X>::percolateDown(u_int curr)
{
    if(isMinHeap())
    {
        u_int min_c;
        // NOTE: Have to add extra dereferencers for pointers
        while(left(curr) < arr.size() && *arr[curr] > *arr[minChild(curr)]) 
        {
            min_c = minChild(curr);
            swap(arr[curr], arr[min_c]);
            curr = min_c;
        }
    }
    else
    {
        u_int max_c;
        while(left(curr) < arr.size() && *arr[curr] < *arr[maxChild(curr)]) 
        {
            max_c = maxChild(curr);
            swap(arr[curr], arr[max_c]);
            curr = max_c;
        }
    }
}

/*
 * Percolate an element up from a heap or sub-heap
 * time: O(d)
 */
template<class X>
void Heap<X>::percolateUp(u_int curr)
{
    if(isMinHeap())
    {
        // NOTE: Have to add extra dereferencers for pointers
        while(curr > 0 && *arr[curr] < *arr[par(curr)]) 
        {
            swap(arr[curr], arr[par(curr)]);
            curr = par(curr);
        }
    }
    else
    {
        while(curr > 0 && *arr[curr] > *arr[par(curr)]) 
        {
            swap(arr[curr], arr[par(curr)]);
            curr = par(curr);
        }
    }
}
