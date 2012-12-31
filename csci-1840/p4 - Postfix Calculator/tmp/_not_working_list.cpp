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

// ToDo: Test this. It's new! 
/* Input:   A const List &
 * Output:  None
 * Return:  A const List &
 * Notes:   Allows for List = List by overloading the assignment operator.
 */
#if 0
const List &List::operator = (const List &l)
{
    List::Node *curr = this->head;
    this->head = l.head;
    delete curr;
    return this;
}

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
        ost << curr->count << ' ' << curr->data << endl;
        curr = curr->next;
    }
    return ost;
}
#endif


/* Input:   A const Word
 * Output:  none
 * Return:  none
 * Notes:   Returns the correct position to insert a Word
 */
List::Node *List::traverse(const Word foo) const
{
    Node *curr = head.next;
    while(curr != &head && curr->data < foo)
    {
        curr = curr->next;
    }
    return curr;
}

/* Input:   A const Word
 * Output:  none
 * Return:  none
 * Notes:   Inserts a Word in the correct position.
 */
void List::insert(const Word foo)
{
    Node *curr = trav(foo);
    if(find(foo))
    {
        ++curr->count;
    }
    else
    {
        List::Node *tmp       = new List::Node(curr->prev, foo, curr);
        tmp->next->prev = tmp->prev->next = tmp;
    }
} // End insert

/* Input:   A const Word foo
 * Output:  none
 * Return:  A boolean
 * Notes:   Removes a Word from the list and returns true on success.
 */
bool List::remove(const Word foo)
{
    Node *curr = trav(foo);
    if(curr != &head && curr->data == foo)
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
    }
}

/* Input:   A const Word 
 * Output:  none
 * Return:  A boolean
 * Notes:   Returns true in the event that the given node exists.
 */
bool List::find(const Word foo) const
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
 * Notes:   Default constructor.
 */
List::List(void) 
   : head(&head, 0, &head, 0)
{ 
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

} // end List destructor
