/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    list.cpp                                                        *
 * Use:     Header definition for the List class. A list allows dynamic     *
 *          data storage. This list stores data of type Word.               *
 ***************************************************************************/
#include<iostream>
using namespace std;

#include<new>

// List and Node class definitions
#include"list.h"  

/* Input:   An ostream & and a const List &
 * Output:  None
 * Return:  An ostream
 * Notes:   Allows for cout << List by overloading the ostream operator.
 */
ostream &operator << (ostream &ost, const List &l)
{
    List::Node *curr = l.head.next; 
    while(curr != &l.head)
    {
        ost << curr->name << '=' << curr->value << endl;
        curr = curr->next;
    }
    return ost;
}

/* Input:   A const Word &
 * Output:  none
 * Return:  none
 * Notes:   Returns the requested position in the List
 */
List::Node *List::traverse(const Word &foo) const
{
    Node *curr = head.next;
    while(curr != &head && curr->name < foo)
    {
        curr = curr->next;
    }
    return curr;
}

/* Input:   Two const Word & (name, value)
 * Output:  none
 * Return:  none
 * Notes:   Inserts a Word in the list in order.
 */
void List::insert(const Word &name, const Word &value)
{
    Node *curr = traverse(name);    // Get the insertion position
    Word foo   = find(name);        // See if the name/value pair exists
    if(foo != NULL)                 // If it does exist
    {
        curr->value = value;        // Just update the value
    }
    else                            // If it does NOT exist
    {
        Node *tmp = new Node(curr, curr->prev, name, value);
        // Insert tmp like so:
        // [prev->next] ---> [tmp] <--- [next->prev]
        tmp->next->prev = tmp->prev->next = tmp; 
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
    if(curr != &head && curr->name == foo)
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        rval = true;    // Node successfully removed
    }
    return rval;
}

/* Input:   A const Word &
 * Output:  none
 * Return:  A Word
 * Notes:   Returns the value for the Word if it is found,
 *          else, it returns NULL.
 */
Word List::find(const Word &foo) const
{
    Word rval  = NULL;
    Node *curr = traverse(foo);    // Traverse to the position in the List
    if(curr != &head && curr->name == foo) 
    {
        // If this is the value we were looking for, return it.
        if(curr->value != NULL)
        {
            rval = curr->value;
        }
        else
        {
            rval = " ";
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
    // while head is not empty remove the name
    while(!empty())
    {
        remove(head.next->name);
    }
} 
