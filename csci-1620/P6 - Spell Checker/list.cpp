/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    list.cpp                                                        *
 * Use:     A list allows dynamic                                           *
 *          data storage. This list stores data of type Word.               *
 ***************************************************************************/
#include<iostream>
using namespace std;

// List and Node class definitions
#include"list.h"

/* Input:   An ostream & and a const List &
 * Output:  None
 * Return:  An ostream
 * Notes:   Allows for cout << List by overloading the ostream operator.
 */
ostream &operator << (ostream &ost, const List &l)
{
    char buffer[128];                   // Dummy buffer for getline
    List::Node *curr = l.head.next;     // head.next
    for(int counter = 1; curr != &l.head; ++counter) // loop while curr != head
    {
        ost << counter << " : " << curr->data << endl; // 1 : dictionaryword
        curr = curr->next;  // increment curr
        if(counter % 20 == 0) // page at 20 lines
        {
            ost << "Continued ..." << endl; 
            cin.getline(buffer, 128);   // Use getline to page
        }
    }
    return ost;
}


/* Input:   None
 * Output:  None
 * Return:  An int
 * Notes:   Returns the "size" of the list which is the number of elements.
 */
int List::size(void)
{
    return count; 
}


/* Input:   A const int
 * Output:  None
 * Return:  A const Word
 * Notes:   This returns an element of a list, which is a word
 */
const Word &List::operator [] (const int n) const
{
    static Word *rval;  // if the value was not valid, return a blank word ref
    if(n < count)
    {
        Node *curr = head.next; // start looping here
        for(int i = 1; i < n; ++i)
        {
            curr = curr->next;  // increment curr
        }
        rval = &curr->data;     // this is the data we want to return
    }
    else // if n wasn't a valid number return a blank word reference
    {
        rval = (const_cast<Word *>(&head.data));
    }
    return *rval;
}

/* Input:   A const Word &
 * Output:  none
 * Return:  Node *
 * Notes:   Returns the requested position in the List
 */
List::Node *List::traverse(const Word &foo) const
{
    Node *curr = head.next;
    while(curr != &head && curr->data < foo)
    {
        curr = curr->next;
    }
    return curr;
}

/* Input:   Two const Word & (data)
 * Output:  none
 * Return:  none
 * Notes:   Inserts a Word in the list in order.
 */
void List::insert(const Word &data)
{
    Node *curr = traverse(data);        // Get the insertion position
    if(curr->data != data)              // If it does not exist
    {
        Node *tmp = new Node(curr, curr->prev, data);
        // Insert tmp like so:
        // [prev->next] ---> [tmp] <--- [next->prev]
        tmp->next->prev = tmp->prev->next = tmp; 
        ++count;    // increment counter
    }
} // End insert

/* Input:   A const Word foo &
 * Output:  none
 * Return:  A boolean
 * Notes:   Removes a Word from the list and returns true on success.
 */
bool List::remove(const Word & foo)
{
    bool rval  = false; // Will return false if node doesn't get removed
    Node *curr = traverse(foo);
    if(curr != &head && curr->data == foo)
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        rval = true;    // Node successfully removed
        --count;
    }
    return rval;
}

/* Input:   A const Word &
 * Output:  none
 * Return:  A Word
 * Notes:   Returns the value for the Word if it is found,
 *          else, it returns NULL.
 */
bool List::find(const Word &foo) const
{
    bool rval  = false;
    Node *curr = traverse(foo);    // Traverse to the position in the List
    if(curr != &head && curr->data == foo) 
    {
        // If this is the value we were looking for, return it.
        if(curr->data != NULL)
        {
            rval = true;
        }
        else
        {
            rval = false;
        }

    }
    // Else return NULL
    return rval;
}
        

/* Input:   none
 * Output:  none
 * Return:  A boolean
 * Notes:   Returns true in the event that the list is empty.
 */
bool List::empty(void) const 
{ 
   return head.next == &head;   // If the List is empty, the head will be NULL
} 


/* Input:   none
 * Output:  none
 * Return:  none
 * Notes:   Destructor.
 */
List::~List()
{
    // while head is not empty remove the data
    while(!empty())
    {
        remove(head.next->data);
    }
} 
