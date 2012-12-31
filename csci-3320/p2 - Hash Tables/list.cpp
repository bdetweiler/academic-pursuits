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
    // Dummy buffer for getline
    // char buffer[LIST_BUF_LEN];
    // head.next
    List::Node *curr = l.head.next;
    // loop while curr != head
    for(int counter = INDEX_START; curr != &l.head; ++counter)
    {
        // Old Way - "1 : dictionaryword"
        // ost << counter << " : " << curr->data << endl;
        // New Way - "dictionaryword"
        ost << curr->data << endl;
        // increment curr
        curr = curr->next;
        // page at 20 lines. UPDATE: NO PAGING RIGHT NOW.
        /*
        if(counter % PAGER == 0)
        {
            ost << "Continued ..." << endl; 
            Use getline to page
            cin.getline(buffer, LIST_BUF_LEN);
        }
        */
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
const char* List::operator[] (const u_int n) const
{
    // if the value was not valid, return a blank word ref
    static char* rval;
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
        rval = (const_cast<char *>(head.data));
    }
    return rval;
}

/* traverse()
 * ---
 * Input:   const u_int
 * Output:  none
 * Return:  const char*
 * Big-O:   O(n) - if n is at the end, will have to traverse all 
 *          of the elements. 
 * Notes:   Returns the data at the requested element.
 */
List::Node *List::traverse(const char* foo) const
{
    Node *curr = head.next;
    while(curr != &head && strncasecmp(curr->data, foo, LIST_BUF_LEN))
        curr = curr->next;
    return curr;
}

/* setSoundex()
 * ---
 * Input:   const char*
 * Output:  none
 * Return:  none
 * Big-O:   N/A
 * Notes:   Sets the soundex code for the List of corresponding entries.
 */
void List::setSoundex(const char* foo)
{
    strncpy(soundex, foo, SOUNDEX_LEN);
    soundex[SOUNDEX_LEN] = '\0';
}

/* getSoundex()
 * ---
 * Input:   none
 * Output:  none
 * Return:  char*
 * Big-O:   N/A
 * Notes:   returns the soundex code for the current List.
 */
char* List::getSoundex(void)
{
    return soundex;
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
void List::insert(char* data)
{
    // Get the insertion position
    Node* curr = traverse(data);
    // If it does not exist
    if(curr->data != data)
    {
        Node* tmp = new Node(curr, curr->prev, data);
        // Insert tmp like so:
        // [prev->next] ---> [tmp] <--- [next->prev]
        tmp->next->prev = tmp->prev->next = tmp; 
        ++listLen;
        sort();
    }
} 

/* alphaCheck()
 * ---
 * Input:   const char*, const char*
 * Output:  none
 * Return:  none 
 * Big-O:   N/A
 * Notes:   Gets the alphabetical order of two words, ala strcmp,
 * TODO:    Clean this up
 */
int List::alphaCheck(const char* foo, const char* bar)
{
    int rval = 0;
    size_t fooLen = strlen(foo);
    size_t barLen = strlen(bar);

    if(fooLen >= barLen)
    {
        for(u_int i = 0; i < fooLen && !rval; ++i)
        {
            if(tolower(foo[i]) < tolower(bar[i]))
                rval = -1;
            else if(tolower(foo[i]) > tolower(bar[i]) || bar[i] == '\0')
                rval = 1;
        }
    }
    else
    {
        for(u_int i = 0; i < barLen && !rval; ++i)
        {
            if(tolower(bar[i]) < tolower(foo[i]))
                rval = 1;
            else if(tolower(bar[i]) > tolower(foo[i]) || foo[i] == '\0')
                rval = -1;
        }
    }

    return rval;
    
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
            if(alphaCheck(curr->data, compare->data) > 0)
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
    char tmp[LIST_BUF_LEN];

    strncpy(tmp, foo->data, LIST_BUF_LEN);
    strncpy(foo->data, bar->data, LIST_BUF_LEN);
    strncpy(bar->data, tmp, LIST_BUF_LEN);

}

/* remove()
 * ---
 * Input:   const char*
 * Output:  none
 * Return:  bool 
 * Big-O:   O(n)
 * Notes:   Removes a node from the list
 */
bool List::remove(const char* foo)
{
    bool rval  = false; // Will return false if node doesn't get removed
    Node *curr = traverse(foo);
    if(curr != &head && !strncasecmp(curr->data, foo, LIST_BUF_LEN))
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        // Node successfully removed
        rval = true;
        // we're about to decrement an unsigned value. Bad. Exit.
        if(!listLen)
            exit(1);
        --listLen;
    }
    return rval;
}

/* find()
 * ---
 * Input:   const char*
 * Output:  none
 * Return:  bool 
 * Big-O:   O(n)
 * Notes:   Finds a node based on the data given
 */
bool List::find(const char* foo) const
{
    bool rval = false;
    // Traverse to the position in the List
    Node *curr = traverse(foo);
    if(curr != &head && strncasecmp(curr->data, foo, strlen(foo)) == 0) 
    {
        // If this is the value we were looking for, return it.
        if(curr->data != NULL)
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
   return head.next == &head;   // If the List is empty, the head will be NULL
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
    memset(soundex, '\0', SOUNDEX_LEN);
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
