/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    list.h                                                          *
 * Use:     Template for the List<T> class. A list allows dynamic           *
 *          data storage. This is a templated doubly-circularly linked      *
 *          list.                                                           *
 *                                                                          *
 *          This also contains templates for Node<T> and Iterator<T>        *
 ***************************************************************************/
#ifndef LIST_H
#define LIST_H

// Where to index the list in terms of printing 
#define INDEX_START     0
#define LIST_BUF_LEN    256
#define PAGER           20

// Used to dereference the object that is currently stored in the list.
// Use one star for an object, two for a pointer to an object
#define DEREF           **

// Errors
#define OOBERROR 99

#include<cassert>
#include<iostream>
using namespace std;
//using std::endl;
//using std::cout;
//using std::cerr;

#include<cmath>
using std::floor;

typedef unsigned int u_int;

namespace List
{

template<typename T> class List;
template<typename T> class Iterator;

/* class Node
 * ---
 * Defines a node, which is an container for each piece of list data.
 */
template<typename T>
class Node
{
    private:
        // The next node in the list.
        Node *next;                 
        // The previous node in the list.
        Node *prev;                 
        // The vertex name
        T data;

    public:
        /* Default Constructor
         * ---
         * Input:   none
         * Output:  none
         * Return:  none
         * Big-O:   O(1)
         * Notes:   Creates a new Node which defaults each pointer to NULL.
         */
        Node(Node* n = 0, Node* p = 0, T d = 0)
            : next(n), prev(p), data(d) {;;;}
    
   friend class List<T>;
   friend class Iterator<T>;

}; // end class Node

/* class Iterator
 * ---
 * Defines an Iterator, which is basically a fancy pointer to a node
 * in the list. It can be manipulated using most of the typical operators.
 * To get the value at the current position, use the dereference operator.
 */
template<typename T>
class Iterator
{
    private:
        Node<T>* pos;
    
    public:
        /* Default Constructor / Copy Constructor
         * ---
         * Input:   none
         * Output:  none
         * Return:  none
         * Big-O:   O(1)
         * Notes:   Creates a new Iterator and defaults the pos pointer to NULL.
         */
        Iterator(Node<T>* p = NULL)
            : pos(p)
            {;;;}

        /* Assignment Operator
         * ---
         * Input:   Node<T>*
         * Output:  none
         * Return:  none
         * Big-O:   O(1)
         * Notes:   Assigns a Node<T>* as the pos of the Iterator
         */
        Iterator operator= (Node<T>* foo)
        {
            pos = foo;
            return *this;
        }
        
        /* Assignment Operator
         * ---
         * Input:   Node<T>*
         * Output:  none
         * Return:  none
         * Big-O:   O(1)
         * Notes:   Assigns a Node<T>* as the pos of the Iterator
         */
        Iterator operator= (Iterator<T> foo)
        {
            pos = foo.pos;
            return *this;
        }

        /* getPos()
         * ---
         * Input:   none
         * Output:  none
         * Return:  Node<T>*
         * Big-O:   O(1)
         * Notes:   Allows non-Friend access to the actual Node<T>* pointed
         *          to by pos.
         */
        Node<T>* getPos(void)
        { return pos; }

        /* Dereference Operator
         * ---
         * Input:   none
         * Output:  none
         * Return:  T
         * Big-O:   O(1)
         * Notes:   If the current Node<T> pointed to by pos isn't NULL, 
         *          go ahead and return the value in it.
         */
        T operator* (void) const
        {
            assert(pos != NULL);
            return pos->data;
        }

        /* += Operator
         * ---
         * Input:   const int
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T> += int.
         * Example: 
         *      Iterator<T> iter = list.begin();
         *      iter += 5;
         *      Will move the Iterator 5 nodes past begin() and return the 
         *      Iterator at that position.
         */
        Iterator<T> operator+= (const int foo)
        {
            if(pos)
                if(foo >= 0)
                    for(int i = 0; i < foo; ++i)
                        pos = pos->next;
                // If foo was a negative number
                else
                    for(int i = 0; i > foo; --i)
                        pos = pos->prev;
            else
            {
                cerr << "Error: Out of Bounds Error. \n"
                     << "You tried to add to an Iterator "
                     << "with no initial position." << endl;
                exit(OOBERROR);
            }

            return *this;
        }
        
        /* -= Operator
         * ---
         * Input:   const int
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T> -= int.
         * Example: 
         *      Iterator<T> iter = list.end();
         *      iter -= 5;
         *      Will move the Iterator 5 nodes before end() and return the 
         *      Iterator at that position.
         */
        Iterator<T> operator-= (const int foo)
        {
            if(pos)
                if(foo >= 0)
                    for(int i = 0; i < foo; ++i)
                        pos = pos->prev;
                // If foo was a negative number
                else
                    for(int i = 0; i > foo; --i)
                        pos = pos->next;
            else
            {
                cerr << "Error: Out of Bounds Error. \n"
                     << "You tried to subtract from an Iterator "
                     << "with no initial position." << endl;
                exit(OOBERROR);
            }

            return *this;
        }

        /* ++ Operator (POST-Increment)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T>++.
         * Example: 
         *      Iterator<T> iter = list.begin();
         *      iter++;
         *      Will move the Iterator one node past begin() and return
         *      the Iterator at that position
         * TODO:    This is not behaving properly. 
         *          It is actually PRE Incrementing.
         */
        /*
        Iterator<T> operator++ (int dummy)
        {
            Iterator<T> rval = *this;

            if(pos)
            {
                rval.pos = pos->next;
                pos = pos->next;
            }
            else
            {
                cerr << "Error: Out of Bounds Error. \n"
                     << "You tried to add to an Iterator "
                     << "with no initial position." << endl;
                exit(OOBERROR);
            }

            return rval;
        }
        */
        
        /* ++ Operator (PRE-Increment)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for ++Iterator<T>.
         * Example: 
         *      Iterator<T> iter = list.begin();
         *      ++iter;
         *      Will move the Iterator one node past begin() and return
         *      the Iterator at that position
         */
        Iterator<T>& operator++ (void)
        {
            if(pos)
                pos = pos->next;
            else
            {
                cerr << "Error: Out of Bounds Error. \n"
                     << "You tried to add to an Iterator "
                     << "with no initial position." << endl;
                exit(OOBERROR);
            }

            return *this;
        }

        /* + Operator (Addition)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T> + int.
         * Example: 
         *      Iterator<T> iter = list.begin();
         *      iter = iter + 1;
         *      Will move the Iterator one node past begin() and return
         *      the Iterator at that position
         */
        Iterator<T> operator+ (const int n) const
        {
            Iterator<T> rval = *this;
            if(pos)
            {
                if(n > 0)
                    for(int i = 0; i < n; ++i)
                        rval.pos = rval.pos->next;
                // n is a negative number
                else
                    for(int i = 0; i > n; --i)
                        rval.pos = rval.pos->prev;
            }
            else
            {
                cerr << "Error: Out of Bounds Error. \n"
                     << "You tried to add to an Iterator "
                     << "with no initial position." << endl;
                exit(OOBERROR);
            }
            
            assert(rval.pos != NULL);
        
            return rval;
        }

        /* - Operator (Subtraction)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T> - int.
         * Example: 
         *      Iterator<T> iter = list.end();
         *      iter = iter - 1;
         *      Will move the Iterator one node before end() and return
         *      the Iterator at that position
         */
        Iterator<T> operator- (const int n)
        {
            Iterator<T> rval = *this;
            if(rval.pos)
            {
                if(n < 0)
                    for(int i = 0; i > n; --i)
                        rval.pos = rval.pos->next;
                else
                    for(int i = 0; i < n; ++i)
                        rval.pos = rval.pos->prev;
            }
            else
            {
                cerr << "Error: Out of Bounds Error. \n"
                     << "You tried to subtract from an Iterator "
                     << "with no initial position." << endl;
                exit(OOBERROR);
            }
            
            assert(rval.pos != NULL);
            
            return rval;
        }

        /* -- Operator (POST-Decrement)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T>--.
         * Example: 
         *      Iterator<T> iter = list.end();
         *      iter--;
         *      Will move the Iterator one node before end() and return
         *      the Iterator at that position
         * TODO: This is not behaving appropriately.
         *       It is not actually POST-decrementing.
         */
        /*
        Iterator<T> operator-- (int dummy)
        {
            Iterator<T> iter = *this;
            if(pos)
            {
                iter.pos = pos->prev;
                pos = pos->prev;
            }
            else
            {
                cerr << "Error: Out of Bounds Error. \n"
                     << "You tried to decrement an Iterator "
                     << "with no initial position." << endl;
                exit(OOBERROR);
            }
           
            assert(pos != NULL);
            
            return iter;
        }
        */
        
        /* -- Operator (PRE-Decrement)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for --Iterator<T>.
         * Example: 
         *      Iterator<T> iter = list.end();
         *      --iter;
         *      Will move the Iterator one node before end() and return
         *      the Iterator at that position
         */
        Iterator<T>& operator-- (void)
        {
            if(pos)
                pos = pos->prev;
            else
            {
                cerr << "Error: Out of Bounds Error. \n"
                     << "You tried to decrement an Iterator "
                     << "with no initial position." << endl;
                exit(OOBERROR);
            }
            assert(pos != NULL);
            
            return *this;
        }

        /* == Operator (Equality)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T> == Iterator<T>.
         * Example: 
         *      if(iter == begin())
         *      checks to see if iter is at the beginning.
         */
        bool operator== (Iterator iter) const
        { return pos == iter.getPos(); }

        /* != Operator (Inequality)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T> != Iterator<T>.
         * Example: 
         *      while(iter != end())
         *      runs a command while iter is not at the end.
         */
        bool operator!= (Iterator iter) const
        { return !(*this == iter); }
        
        /* == Operator (Equality)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T> == Node<T>*.
         * Example: 
         *      Node<T>* curr = access;
         *      if(iter == curr)
         *      runs a command while iter is not at the end;
         */
        bool operator== (Node<T>* n) const
        { return pos == n; }
        
        /* != Operator (Inequality)
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Allows for Iterator<T> != Node<T>*.
         * Example: 
         *      Node<T>* curr = access;
         *      while(iter != curr)
         *      runs a command while iter is not at the end;
         */
        bool operator!= (Node<T>* n) const
        { return !(*this == n); }

    friend class List<T>;
}; 

/* class List
 * ---
 * Defines a List, which, in this case, is a doubly-circularly linked list.
 * This list supports most of the features of the STL Vector class.
 */
template<typename T>
class List 
{
    private:
        // Access pointer provides a way to access the list
        Node<T>* access;
        size_t listLen;

    public:

        /* Default Constructor
         * ---
         * Input:   none
         * Output:  none
         * Return:  none
         * Big-O:   O(1)
         * Notes:   Creates a new list setting access pointer to NULL
         */
        List(void) 
        {
            access = NULL;
            listLen = 0;
        }
      
        /* Constructor
         * ---
         * Input:   T
         * Output:  none
         * Return:  none 
         * Big-O:   O(1)
         * Notes:   Creates new list given a T
         */
        List(T data)
        { 
            access = NULL;
            listLen = 0;
            push_back(data); 
        }
        
        
        /* Constructor
         * ---
         * Input:   size_t, T
         * Output:  none
         * Return:  none 
         * Big-O:   O(n)
         * Notes:   Creates new list with num nodes of data.
         */
        List(size_t num, T data)
        { 
            access = NULL;
            listLen = 0;
            // NOTE: push_back will set access and listLen for us.
            for(size_t i = 0; i < num; ++i)
                push_back(data);
        }
        
        /* Constructor
         * ---
         * Input:   T
         * Output:  none
         * Return:  none 
         * Big-O:   O(n)
         * Notes:   Creates new list given a T
         */
        List(Iterator<T> start, Iterator<T> end)
        { 
            access = NULL;
            listLen = 0;
            while(start != end)
            {
                // NOTE: push_back will set access and listLen for us.
                push_back(*start);
                ++start;
            }
            
            // Get the last one
            push_back(*start);
        }
        
        /* Constructor
         * ---
         * Input:   List&
         * Output:  none
         * Return:  none 
         * Big-O:   O(n)
         * Notes:   Creates new list given an existing list
         */
        List(List<T>& list)
        { 
            access = NULL;
            listLen = 0;
            Iterator<T> start = list.begin();
            while(start != list.end())
            {
                push_back(*start);
                ++start;
            }
            
            // Get the last one
            push_back(*start);
        }

        /* begin()
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Returns an Iterator to the first element in the list.
         */
        Iterator<T> begin(void)
        { 
            static Iterator<T> rval = NULL;
            if(!empty())
                rval = access->next; 
            
            return rval;
        }

        /* end()
         * ---
         * Input:   none
         * Output:  none
         * Return:  Iterator<T>
         * Big-O:   O(1)
         * Notes:   Returns an Iterator to the last element in the list.
         */
        Iterator<T> end(void)
        { 
            Iterator<T> rval;
            if(!empty())
                rval = access; 
            return rval;
        }
        
        /* back()
         * ---
         * Input:   none
         * Output:  none
         * Return:  T
         * Big-O:   O(1)
         * Notes:   Returns the value at the end of the list
         */
        T back(void)
        { 
            T rval;
            if(access != NULL)
                rval = access->data; 
            
            return rval;
        }

        /* front()
         * ---
         * Input:   none
         * Output:  none
         * Return:  T
         * Big-O:   O(1)
         * Notes:   Returns the value at the front of the list
         */
        T front(void)
        { 
            T rval;
            if(access != NULL)
                rval = access->next->data;
            
            return rval;
        }

        /* erase()
         * ---
         * Input:   Iterator<T>
         * Output:  none
         * Return:  T
         * Big-O:   O(1)
         * Notes:   Erases an element at the given Iterator location
         */
        Iterator<T> erase(Iterator<T> loc)
        {
            Iterator<T> rval = loc + 1;
            remove(loc.getPos());
            loc = rval;
            return rval;
        }
        
        /* erase()
         * ---
         * Input:   Iterator<T>, Iterator<T>
         * Output:  none
         * Return:  T
         * Big-O:   O(n)
         * Notes:   Erases a number of elements from start to end;
         */
        Iterator<T> erase(Iterator<T> start, Iterator<T> end)
        {
            Iterator<T> rval = start + 1;
            while(start != end)
            {
                remove(start.getPos());
                start = rval;
                rval = start + 1;
            }
            // Get that last one
            remove(start.getPos());
            return rval;
        }

        /* reverse()
         * ---
         * Input:   none
         * Output:  none
         * Return:  none
         * Big-O:   O(n)
         * Notes:   Reverses the order of elements in the list in linear time.
         */
        void reverse(void)
        {
            Iterator<T> start = begin();
            Iterator<T> fin = end();
            for(int i = 0; i <= floor(static_cast<double>(listLen / 2)); ++i)
            {
                swap(start.pos, fin.pos);
                ++start;
                --fin;
            }
        }

        /* size()
         * ---
         * Input:   void
         * Output:  none
         * Return:  size_t
         * Big-O:   O(1)
         * Notes:   Returns the number of elements in the list.
         */
        const size_t size(void)
        { return listLen; }


        /* operator[]
         * ---
         * Input:   const u_int
         * Output:  none
         * Return:  const T
         * Big-O:   O(n/2) == O(n) Even though we cut the worst-case time
         *          in half by choosing which way to traverse from 
         *          (front or back), n is the dominating term. 
         * Notes:   Returns the value at the requested element
         */
        const T operator[] (const u_int n) const
        {
            T rval;

            // List is Zero-Indexed
            // So if listLen == 1, then n == 0 is valid,
            // but n == 1 is not valid.
            if(n >= listLen)
            {
                cerr << "Error: Out of Bounds Error.\n" <<
                        "Tried to access location " << n << "\n" <<
                        "when list ends at location " << listLen << endl;
                exit(OOBERROR);
            }

            Node<T>* curr = NULL;

            /* If the element is closer by moving backward
             * Example:
             *      listLen = 8;
             *      n = 6;
             *      if((8 - 1) - 6) <        floor((7 / 2))
             *      if((  7  ) - 6) <        floor(( 3.5 ))
             *      if(1 < 3)
             */
            if(((listLen - 1) - n) < (u_int)floor(static_cast<double>(listLen / 2)))
            {
                // Start at the "tail"
                curr = access;
                // Work backwards
                for(u_int i = listLen - 1; i > n; --i)
                    curr = curr->prev;
                
                rval = curr->data;
            }
            // The element is closer by moving foward
            else
            {
                // Start at the "head"
                curr = access->next;
                
                // Work forwards
                for(u_int i = 0; i < n; ++i)
                    curr = curr->next;
                
                rval = curr->data;
            }                    

            return rval;
        }

        /* overwrite
         * ---
         * Input:   u_int, T
         * Output:  none
         * Return:  none
         * Big-O:   O(n/2) == O(n) Even though we cut the worst-case time
         *          in half by choosing which way to traverse from 
         *          (front or back), n is the dominating term. 
         * Notes:   Overwrites the value at the requested position
         */
        void overwrite(u_int index, T foo)
        {
            Node<T>* curr = NULL;

            if(((listLen - 1) - index) < (u_int)floor(static_cast<double>((listLen / 2))))
            {
                curr = access;
                for(u_int i = listLen - 1; i > index; --i)
                    curr = curr->prev;
                
                curr->data = foo;
            }
            else
            {
                curr = access->next;
                for(u_int i = 0; i < index; ++i)
                    curr = curr->next;
                
                curr->data = foo;
            }
        }

        /* findFirstOf()
         * ---
         * Input:   const T
         * Output:  none
         * Return:  Node<T>*
         * Big-O:   O(n) - if n is at the end, will have to traverse all 
         *          of the elements. 
         * Notes:   Returns the first instance of the requested data
         */
        Iterator<T> findFirstOf(T foo)
        {
            Iterator<T> curr(access->next);

            // Traverse the list until we either find our element,
            // or run full circle
            while(curr != end() && *curr != foo)
                ++curr;

            // If we didn't find the data requested, return NULL
            if(*curr != foo)
                curr = NULL;

            return curr;
        }

        /* insertAfter()
         * ---
         * Input:   T, T
         * Output:  none
         * Return:  bool 
         * Big-O:   O(1)
         * Notes:   Inserts a value after first occurance of target
         */
        bool insertAfter(T target, T val)
        {
            bool rval = false;
            
            // Get the insertion position
            Node<T>* curr = (findFirstOf(target)).pos->next;

            // If it does not exist
            if(curr)
            {
                Node<T>* tmp = new Node<T>(curr, curr->prev, val);
                // Insert tmp like so:
                // [prev->next] ---> [tmp] <--- [next->prev]
                tmp->next->prev = tmp->prev->next = tmp; 
                ++listLen;
                rval = true;
            }
            return rval;
        } 
        
        
        /* insertAfter()
         * ---
         * Input:   Iterator<T>, T
         * Output:  none
         * Return:  bool 
         * Big-O:   O(1)
         * Notes:   Inserts a value after first occurance of target
         */
        bool insertAfter(Iterator<T> target, T val)
        {
            bool rval = false;
            // Get the insertion position

            // If it does not exist
            if(target != NULL)
            {
                Node<T>* tmp = new Node<T>(target.pos->next, target.pos, val);
                // Insert tmp like so:
                // [prev->next] ---> [tmp] <--- [next->prev]
                tmp->next->prev = tmp->prev->next = tmp; 
                ++listLen;
                rval = true;
            }
            return rval;
        } 
        
        /* insertBefore()
         * ---
         * Input:   T, T
         * Output:  none
         * Return:  bool 
         * Big-O:   O(1)
         * Notes:   Inserts a value before target
         */
        bool insertBefore(T target, T val)
        {
            bool rval = false;
            
            // Get the insertion position
            Node<T>* curr = (findFirstOf(target)).pos;

            // If it does not exist
            if(curr)
            {
                Node<T>* tmp = new Node<T>(curr, curr->prev, val);
                // Insert tmp like so:
                // [prev->next] ---> [tmp] <--- [next->prev]
                tmp->next->prev = tmp->prev->next = tmp; 
                ++listLen;
                rval = true;
            }
            return rval;
        } 
        
        /* insertBefore()
         * ---
         * Input:   Iterator<T>, T
         * Output:  none
         * Return:  bool 
         * Big-O:   O(1)
         * Notes:   Inserts a value after first occurance of target
         */
        bool insertBefore(Iterator<T> target, T val)
        {
            bool rval = false;
            // Get the insertion position

            // If it does not exist
            if(target != NULL)
            {
                Node<T>* tmp = new Node<T>(target.pos, target.pos->prev, val);
                // Insert tmp like so:
                // [prev->next] ---> [tmp] <--- [next->prev]
                tmp->next->prev = tmp->prev->next = tmp; 
                ++listLen;
                rval = true;
            }
            return rval;
        } 
        
        /* push_back()
         * ---
         * Input:   T
         * Output:  none
         * Return:  none
         * Big-O:   O(1)
         * Notes:   Inserts a given value into the list at the back.
         */
        void push_back(T val)
        {
            
            // Set up the node so it is pointing to itself
            Node<T>* n = new Node<T>(n, n, val);
            // If list is not empty
            if(access)
            {
                /* Example:
                 *      
                 *                 [access]
                 *                    |
                 *                    V
                 *      <--[Y]--> <--[Z]--> <--[A]-->
                 * 
                 *      list.push_back(n)
                 *                        [access] 
                 *                           |
                 *                           V
                 *      [Y]--> <--[Z]--> <--[n]--> <--[A]-->
                 */
                n->prev = access;
                if(listLen > 1)
                {
                    n->next = access->next;
                    access->next->prev = n;
                    access->next = n;
                }
                // Special case for the single element list
                else
                {
                    n->next = access;
                    access->next = n;
                    access->prev = n;
                }
                
            }
            // Finally, reset access pointer to n;
            access = n;
            if(!listLen)
                access->next = access->prev = access;
            // Update list size;
            ++listLen;
        } 
        
        
        /* push_front()
         * ---
         * Input:   T
         * Output:  none
         * Return:  T 
         * Big-O:   O(1)
         * Notes:   Inserts a given value into the list at the front.
         */
        void push_front(T val)
        {
            Node<T>* n = new Node<T>(n, n, val);
            if(access)
            {
                n->prev = access;

                if(listLen > 1)
                {
                    n->next = access->next;
                    access->next->prev = n;
                    access->next = n;
                }
                else
                {
                    n->next = access;
                    access->next = n;
                    access->prev = n;
                }
            }
            else
            {
                access = n;
                access->next = access->prev = access;
            }

            ++listLen;
        } 

        /* pop_back()
         * ---
         * Input:   T
         * Output:  none
         * Return:  T 
         * Big-O:   O(1)
         * Notes:   Pops a node at the back of the list.
         */
        T pop_back(void)
        {
            T rval;

            Node<T>* n = NULL;

            if(access)
            {
                n = access;

                if(listLen > 1)
                {
                    access->prev->next = access->next;
                    access->next->prev = access->prev;
                    access = access->prev;
                }
                else
                    access = NULL;

                // Set the return value
                rval = n->data;

                delete n;
            }
            else
            {
                cerr << "Error: Out of Bounds Error.\n"
                     << "Tried to pop an element in the list "
                     << "when there are no elements in the list." << endl;
                exit(OOBERROR);
            }
            
            --listLen;

            return rval;
        } 

        /* pop_front()
         * ---
         * Input:   T
         * Output:  none
         * Return:  T 
         * Big-O:   O(1)
         * Notes:   Pops an element at the front of the list
         */
        T pop_front(void)
        {
            T rval;

            Node<T>* n = NULL;

            if(access)
            {
                n = access->next;

                if(listLen > 1)
                {
                    access->next = n->next;
                    n->next->prev = access;
                }
                else
                    access = NULL;
                
                rval = n->data;

                delete n;
            }
            else
            {
                cerr << "Error: Out of Bounds Error.\n"
                     << "Tried to pop an element in the list "
                     << "when there are no elements in the list." << endl;
                exit(OOBERROR);
            }

            --listLen;

            return rval;
        } 

        /* uniq()
         * ---
         * Input:   none
         * Output:  none
         * Return:  none 
         * Big-O:   
         * Notes:   Removes all consecutive duplicate values from the list.
         *          You may need to sort() the list to get the desired result.
         */
        void uniq(void)
        {
            Node<T>* curr = access->next;
            Node<T>* compare = NULL;

            /* Gotta grab listLen now, because when we start
             * removing elements, we're going to be
             * decrementing the listLen and we won't be 
             * able to hit all the elements.
             */
            size_t len = listLen;

            for(size_t i = 1; i < listLen; ++i)
            { 
                /* [1][2][2][2][3]
                 *      curr == 1
                 *      compare == 2
                 * Next iteration:
                 *      curr == 2
                 *      compare == 2 
                 *      remove the second 2
                 * Etc.
                 *
                 * Result:
                 * [1][2][3]
                 */
                 
                compare = curr->next;
                
                for(size_t j = i + 1; j < len; ++j)
                {
                    if(curr->data == compare->data)
                    { 
                        compare = compare->next;
                        remove(compare->prev);
                    }
                    else
                        break;

                }
                
                curr = curr->next;
            }
        }

        /* sort()
         * ---
         * Input:   none
         * Output:  none
         * Return:  none 
         * Big-O:   TODO: Need to use a better sort algorithm.
         * Notes:   Sorts the list based on the > operator. 
         *         
         */
        void sort(void)
        {
            Node<T>* curr = access->next;
            Node<T>* compare = NULL;

            for(size_t i = 1; i <= listLen; ++i)
            { 
                // [head][1][2][3][4][5][tail]
                //      curr == 1
                //      compare == 2
                // Next iteration:
                //      curr == 2
                //      compare == 3
                compare = curr->next;
                
                for(size_t j = i + 1; j <= listLen; ++j)
                {
                    if(curr->data > compare->data)
                        swap(curr, compare);

                    compare = compare->next;
                }
                
                curr = curr->next;
            }

        }
        
        /* swap()
         * ---
         * Input:   Node<T>*, Node<T>*
         * Output:  none
         * Return:  none 
         * Big-O:   N/A
         * Notes:   Swaps two nodes' vertex.
         */
        void swap(Node<T>* foo, Node<T>* bar)
        {
            T tmp = foo->data;
            foo->data = bar->data;
            bar->data = tmp;
        }

        /* remove()
         * ---
         * Input:   const Node<T>*
         * Output:  none
         * Return:  bool 
         * Big-O:   O(n)
         * Notes:   Removes a node from the list. 
         *          Defaults to the last element in the list.
         */
        void remove(Node<T>* foo = NULL)
        {
            if(!empty())
            {
                // Defaults to the access node if no argument was supplied
                if(!foo)
                    foo = access;

                if(listLen > 1)
                {
                    foo->next->prev = foo->prev;
                    foo->prev->next = foo->next;

                    // Move access pointer back one
                    if(foo == access)
                        access = foo->prev;

                }
                else
                    // List is about to be empty. Get rid of access pointer.
                    access = NULL;
                
                delete foo;
                --listLen;

            }
            // we're about to remove an element from the list 
            // that doesn't exist.
            else
            {
                cerr << "Error: Out of Bounds Error.\n" 
                     << "You were about to remove an element "
                     << "from an empty list." << endl;
                exit(OOBERROR);
            }
        }

        /* find()
         * ---
         * Input:   const T
         * Output:  none
         * Return:  bool 
         * Big-O:   O(n)
         * Notes:   Returns true if the given value exists in the list
         */
        bool find(const T foo)
        {
            bool rval = false;

            // Find the first occurance of foo in the list
            Iterator<T> curr = findFirstOf(foo);

            if(curr != NULL)
                // If this is the value we were looking for, return it.
                rval = true;

            // Else return NULL
            return rval;
        }

        /* assign()
         * ---
         * Input:   size_t, const T
         * Output:  none
         * Return:  none
         * Big-O:   O(n) - If num is n, we have to go through all of them.
         * Notes:   Assigns num copies of val starting from the beginning,
         *          overwriting whatever was there before it.
         */
        void assign(size_t num, const T val)
        {
            Node<T>* n = access->next;
            size_t i;
            
            // Overwrite old nodes
            for(i = 0; i < num && i < listLen; ++i)
            {
                n->data = val;
                n = n->next;
            }

            // Create new nodes as needed
            for(; i < num; ++i)
            {
                Node<T>* node = new Node<T>(n, n->next, val);
                n->next->prev = node;
                n->next = node;
                ++listLen;
            }

        }    
                 
        /* assign()
         * ---
         * Input:   Iterator<T>, Iterator<T>
         * Output:  none
         * Return:  none
         * Big-O:   O(n)
         * Notes:   Copies elements from another list to this one, starting at
         *          start and ending at end. This overwrites whatever was in 
         *          this list to begin with.
         */
        void assign(Iterator<T> start, Iterator<T> end)
        {
            Node<T>* n = access->next;
            while(start != end)
            {
                n->data = *start;

                n = n->next;
                ++start;
            }
            // Don't forget the last one
            n->data = *start;
        }    

        /* splice()
         * ---
         * Input:   List<T>&, Iterator<T>
         * Output:  none
         * Return:  none
         * Big-O:   O(1)
         * Notes:   Splices two lists together. No copying is done. 
         *          One list is just concatenated to the other, and therefore
         *          runs in constant time.
         */
        void splice(List<T>& list, Iterator<T> thisBegin = NULL)
        {
            Iterator<T> lEnd = list.end();
            Iterator<T> lBegin = list.begin();
            /* If thisBegin was not specified, the default action is to 
             * try to connect end() with list.begin()
             * and begin() with list.end().
             * Example:
             *      this = <--[thisBegin]--> <--[1]--> <--[2]--> <--[thisEnd]-->
             *      list = <--[lBegin]--> <--[5]--> <--[lEnd]-->
             *      Just cat one on to the end of the other and wrap it around.
             */
            if(thisBegin == NULL)
                thisBegin = begin(); 
           
            // If thisBegin is begin(), thisEnd is end()
            Iterator<T> thisEnd = thisBegin;
            --thisEnd;

            lEnd.pos->next = thisBegin.pos;
            thisBegin.pos->prev = lEnd.pos;

            thisEnd.pos->next = lBegin.pos;
            lBegin.pos->prev = thisEnd.pos;


            // Update the size
            listLen += list.size();

            access = lEnd.pos;

            /* Can only have one access pointer. 
             * Otherwise, we will get a double-free because
             * the destructor will try to delete this list and
             * the one we just spliced with. The list we just spliced with
             * is pretty much ours now. So no further operations should be
             * done with it.
             */
            list.access = NULL;
            list.listLen = 0;
        }

        /* empty()
         * ---
         * Input:   none
         * Output:  none
         * Return:  bool 
         * Big-O:   O(n)
         * Notes:   Returns true or false if the list is empty or not.
         */
        bool empty(void) const 
        { return(access == NULL); } 

        /* clear()
         * ---
         * Input:   none
         * Output:  none
         * Return:  none 
         * Big-O:   O(n)
         * Notes:   Clears the list
         */
        void clear(void)
        {
            while(!empty())
                remove(access);
            
            listLen = 0;
        } 



        /* Destructor
         * ---
         * Input:   none
         * Output:  none
         * Return:  none 
         * Big-O:   O(n)
         * Notes:   Clears the list when the list goes away.
         */
        ~List()
        { clear(); } 



    friend class Iterator<T>;

};

/* operator<<
 * ---
 * Input:   ostream&, const List&
 * Output:  none
 * Return:  ostream&
 * Big-O:   O(n) - Must print every element in the list.
 * Notes:   Overloads the << operator to allow for cout << list;
 */
template<typename T>
inline ostream& operator<< (ostream &ost, List<T> &list)
{
    // Dummy buffer for getline
    char buffer[LIST_BUF_LEN];

    Iterator<T> iter = list.begin();

    //List::Node<T>* curr = list.access->next;
    // loop while curr != head
    for(u_int counter = INDEX_START; 
        counter < list.size() && (iter != NULL); 
        ++counter, ++iter)
    {
        // This prints a number and a colon before the data - "1 : data"
        ost << counter << " : ";
        
        // TODO: Depending on data type, may have to double-dereference
        ost << DEREF iter << endl;
       
        // increment curr
        // page at 20 lines.
        if(counter + 1 % PAGER == 0)
        {
            ost << "Continued ..." << endl; 
            // Use getline to page
            cin.getline(buffer, LIST_BUF_LEN - 1);
        }
    }
    return ost;
}
} // namespace List
#endif
