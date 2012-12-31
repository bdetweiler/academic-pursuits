/****************************************************************************
 * File:    list.cpp                                                        *
 * Author:  Brian Detweiler                                                 *
 * Use:     A list allows dynamic                                           *
 *          data storage. This list stores data of type char*.              *
 ***************************************************************************/

#include<iostream>
using namespace std;

// List and Node class definitions
#include"list.h"

/* operator<<
 * ---
 * Input:   ostream&, const List&
 * Output:  none
 * Return:  ostream&
 * Big-O:   O(n) - Must go through every element in the list.
 * Notes:   Overloads the << operator to allow for cout << list;
 */
ostream& operator<< (ostream &ost, const List &l)
{
    List::Node *curr = l.head.next;

    char ch[HEX_LEN] = "\0";
    while(curr != &l.head)
    {
        // If it's a space, or other non printable,
        // print out the char in hex form
        if(isspace(curr->data) || !isprint(curr->data))
        {
            if(curr->data)
                snprintf(ch, HEX_LEN, "%#x", curr->data);
            else
                strncpy(ch, "0x0", HEX_LEN);
            ost << ch;
        }
        else
            ost << curr->data;

        ost << ":" << curr->freq << endl;
        
        // increment curr
        curr = curr->next;
    }
    return ost;
}


/* size()
 * ---
 * Input:   void
 * Output:  none
 * Return:  size_t
 * Big-O:   O(1)
 * Notes:   Returns the number of elements in the list, which is
 *          stored as a private variable.
 */
size_t List::size(void)
{
    return listLen; 
}


/* operator[]
 * ---
 * Input:   const u_int
 * Output:  none
 * Return:  const char*
 * Big-O:   O(n) - if n is at the end, will have to traverse all 
 *          of the elements. 
 * Notes:   Returns the data at the requested element.
 */
const char List::operator[] (const u_int n) const
{
    // if the value was not valid, return a blank word ref
    static char rval;
    if(n < listLen)
    {
        // start looping here
        Node *curr = head.next; 
        for(u_int i = 1; i < n; ++i)
        {
            // increment curr
            curr = curr->next;
        }
        // this is the data we want to return
        rval = curr->data;
    }
    // if n wasn't a valid number return a blank word reference
    else 
    {
        rval = head.data;
    }
    return rval;
}

const List::Node* List::peek(void) const
{
    return head.next; 
}

/* traverse()
 * ---
 * Input:   const char
 * Output:  none
 * Return:  Node*
 * Big-O:   O(n) - if n is at the end, will have to traverse all 
 *          of the elements. 
 * Notes:   Returns the node at the requested char, or at the end of the list.
 */
List::Node* List::traverse(const char foo) const
{
    Node *curr = head.next;
    while(curr && curr != &head && curr->data != foo)
        curr = curr->next;
    
    return curr;
}



/* insert()
 * ---
 * Input:   char*
 * Output:  none
 * Return:  none 
 * Big-O:   TODO: Not sure what the Big-O is here.
 *          Strictly for inserting, it is O(n),
 *          But not sure of what O() is for sort().
 * Notes:   Inserts a given value into the list, 
 *          then calls sort() and sorts it.
 */
void List::insert(char data)
{

    // Get the insertion position
    Node* curr = traverse(data);
    // If it does not exist
    //if(curr->data != data)
    if((!data && curr->freq < 1) || curr->data != data)
    {
        Node* tmp = new Node(curr, curr->prev, data, 1);
        // Insert tmp like so:
        // [prev->next] ---> [tmp] <--- [next->prev]
        tmp->next->prev = tmp->prev->next = tmp; 

        ++listLen;
        sort();
    }
    else
        ++curr->freq;
} 

/* sort()
 * ---
 * Input:   none
 * Output:  none
 * Return:  none 
 * Big-O:   TODO
 * Notes:   Need to make sure the list is in sorted alphanumerical order.
 *          Case insensitive (use tolower(char))
 */
void List::sort(void)
{
    Node* curr = head.next;
    Node* compare;

    for(size_t i = 1; i <= listLen; ++i)
    { 
        // [head][1][2][3][4][5]
        //      curr == 1
        //      compare == 2
        // Next iteration:
        //      curr == 2
        //      compare == 3
        compare = curr->next;
        
        for(size_t j = i + 1; j <= listLen; ++j)
        {
            if(curr->freq > compare->freq)
                swap(curr, compare);

            compare = compare->next;
        }
        
        curr = curr->next;
    }
}

/* swap()
 * ---
 * Input:   Node*, Node*
 * Output:  none
 * Return:  none 
 * Big-O:   N/A
 * Notes:   Swaps two nodes' data.
 */
void List::swap(Node* foo, Node* bar)
{
    char ctmp;
    u_short ftmp;

    ctmp = foo->data;
    ftmp = foo->freq;

    foo->data = bar->data;
    foo->freq = bar->freq;

    bar->data = ctmp;
    bar->freq = ftmp;
}

/* remove()
 * ---
 * Input:   const char
 * Output:  none
 * Return:  Node* 
 * Big-O:   O(n)
 * Notes:   Removes a node from the list
 */
List::Node* List::remove(const char foo)
{
    Node* rval = NULL;
    Node* curr = traverse(foo);
    if(curr != &head && curr->data == foo)
    {
        // Macro to unlink curr.
        unlink(curr, rval);

        delete curr;
        // Node successfully removed
        
        // we're about to decrement an unsigned value. Bad. Exit.
        if(!listLen)
            exit(1);

        --listLen;
    }
    return rval;
}

/* remove()
 * ---
 * Input:   none
 * Output:  none
 * Return:  Node* 
 * Big-O:   O(1)
 * Notes:   Removes the first item from the list.
 */
List::Node* List::remove(void)
{
    return remove(head.next->data);
}

/* find()
 * ---
 * Input:   const char*
 * Output:  none
 * Return:  bool 
 * Big-O:   O(n)
 * Notes:   Finds a node based on the data given
 */
bool List::find(const char foo) const
{
    bool rval = false;
    // Traverse to the position in the List
    Node *curr = traverse(foo);
    if(curr != &head && curr->data == foo)
    {
        // If this is the value we were looking for, return it.
        if(curr->data)
            rval = true;
    }
    // Else return NULL
    return rval;
}
        
/* empty()
 * ---
 * Input:   none
 * Output:  none
 * Return:  bool 
 * Big-O:   O(n)
 * Notes:   Returns true or false if the list is empty or not.
 */
bool List::empty(void) const 
{ 
    // If the List is empty, the head will be NULL
   return head.next == &head;   
} 

/* clear()
 * ---
 * Input:   none
 * Output:  none
 * Return:  none 
 * Big-O:   O(n)
 * Notes:   Clears the list
 */
void List::clear(void)
{
    // while head is not empty remove the data
    while(!empty())
        remove(head.next->data);
    
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
List::~List()
{
    clear();
} 
