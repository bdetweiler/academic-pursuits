/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    list.h                                                          *
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
    while(curr !=&l.head)
    {
        ost << curr->data << ' ' << curr->count << endl;
        curr = curr->next;
    }
    return ost;
}

/* Input:   A const Word &
 * Output:  none
 * Return:  none
 * Notes:   Returns the correct position to insert a Word
 */
List::Node *List::traverse(const Word & foo) const
{
    Node *curr = head.next;
    while(curr != &head && curr->data < foo)
    {
        curr = curr->next;
    }
    return curr;
}

/* Input:   A const Word &
 * Output:  none
 * Return:  none
 * Notes:   Inserts a Word in the correct position.
 */
void List::insert(const Word & foo)
{
    Node *curr = traverse(foo);
    if(find(foo))
    {
        ++curr->count;
    }
    else
    {
        Node *tmp       = new Node(foo, curr, curr->prev );
        tmp->next->prev = tmp->prev->next = tmp;
    }
} 

/* Input:   A const Word foo &
 * Output:  none
 * Return:  A boolean
 * Notes:   Removes a Word from the list and returns true on success.
 */
bool List::remove(const Word & foo)
{
    bool rval = false;
    Node *curr = traverse(foo);
    if(curr != &head && curr->data == foo)
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        rval = true;
    }
    return rval;
}

/* Input:   A const Word &
 * Output:  none
 * Return:  A boolean
 * Notes:   Returns true in the event that the given node exists.
 */
bool List::find(const Word & foo) const
{
    Node * curr = traverse(foo);
    return(curr != &head && curr->data == foo);
}
        

/* Input:   none
 * Output:  none
 * Return:  A boolean
 * Notes:   Returns true in the event that the list is empty.
 */
bool List::empty(void) const 
{ 
   return head.next == &head; 
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
