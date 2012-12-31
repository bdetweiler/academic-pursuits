/****************************************************************************
 * File:    dheap.cpp                                                       *
 * Author:  Brian Detweiler                                                 *
 * Use:     A heap is an efficient data structur for finding extreme        *
 *          values. This is a templated heap, and can either be a min or    *
 *          max heap. It supports various features that you would want in a *
 *          heap.                                                           *
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
        void percolate_down(u_int);
        void percolate_up(u_int);
    public:
        Heap(void) : d(2), min_heap(true) {;;;}
        // TODO:
        // Heap(const vector<X>); // Make a heap from a vector
        // Heap(const int*); // Make a heap from an array
        Heap(Heap&);
        ~Heap(void);
        // TODO:
        // Heap & operator = (Heap &);
        const int get_d(void);
        const bool is_min_heap(void);

        void set_d(const int);
        void set_min_heap(const bool);
        vector<X> get_vect(void);
        X get_element_at(const u_int);
        int size(void);
        void insert(X);
        X remove(u_int foo);
        X get_root(void) const;
        void merge(Heap<X> &);
        bool empty(void) const;
        int min_child(int);
        int max_child(int);

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
    this->arr = foo.get_vect();
    this->d = foo.get_d();
    this->min_heap = foo.is_min_heap();
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
vector<X> Heap<X>::get_vect(void)
{
    return arr;
}

/*
 * Grab an element at a certain position in the vector
 * (Basically, a public way to view the vector)
 * time: O(1)
 */
template<class X>
X Heap<X>::get_element_at(const u_int foo)
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
const int Heap<X>::get_d(void)
{
    return this->d;
}

/*
 * Return if it is min heap or not
 * time: O(1)
 */
template<class X>
const bool Heap<X>::is_min_heap(void)
{
    return this->min_heap;
}

/*
 * Set the d of the heap 
 * (how many children per node)
 * time: O(1)
 */
template<class X>
void Heap<X>::set_d(const int foo)
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
void Heap<X>::set_min_heap(const bool foo)
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
    percolate_up(arr.size() - 1);
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
        percolate_down(foo);
    }

    return rval;
}

/* 
 * Return the min child of the current node
 * time: O(d)
 */
template<class X>
int Heap<X>::min_child(int foo) 
{
    int min_child = 0;

    // If the left child is less than the size of the array,
    // find the minimum child of "foo"
	if(left(foo) <= arr.size()) 
    {
        // For right now, all we know is the left child is the min child,
        // until we find out differntly
        min_child = left(foo);
        // i = the left child of foo
        // While it is less than or equal to the right child of foo
        // && while it is less than the size of the array
	    for(u_int i = min_child + 1; i <= right(foo) && i < arr.size(); ++i) 
            // If the value at i is less than the value at the previously
            // assigned min_child
		    if(arr[i] < arr[min_child]) 
                // Reassign the min_child
                min_child = i;
    }
    // Now we have the location of the min_child of foo
	return min_child;
}

/* 
 * Return the max child of the current node
 * time: O(d)
 */
template<class X>
int Heap<X>::max_child(int foo) 
{
    int max_child = 0;

	if(left(foo) <= arr.size()) 
    {
        max_child = left(foo);
	    for(u_int i = max_child + 1; i <= right(foo) && i <= arr.size(); ++i) 
		    if(arr[i] > arr[max_child]) 
                max_child = i;
    }
	return max_child;
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
X Heap<X>::get_root(void) const
{ return arr.front(); }

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
        cout << "test"<< endl;
        insert(bar.remove_root());
    }
}

/*
 * Percolate an element down from a heap or sub-heap
 * time: O(d)
 */
template<class X>
void Heap<X>::percolate_down(u_int curr)
{
    if(is_min_heap())
    {
        u_int min_c;
        // NOTE: Have to add extra dereferencers for pointers
        while(left(curr) < arr.size() && *arr[curr] > *arr[min_child(curr)]) 
        {
            min_c = min_child(curr);
            swap(arr[curr], arr[min_c]);
            curr = min_c;
        }
    }
    else
    {
        u_int max_c;
        while(left(curr) < arr.size() && *arr[curr] < *arr[max_child(curr)]) 
        {
            max_c = max_child(curr);
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
void Heap<X>::percolate_up(u_int curr)
{
    if(is_min_heap())
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
