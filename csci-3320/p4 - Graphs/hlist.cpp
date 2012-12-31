/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    hlist.cpp                                                        *
 * Use:     A hlist allows dynamic                                           *
 *          data storage. This hlist stores data of type char*.              *
 ***************************************************************************/
#include<iostream>
using namespace std;

// hList and Node class definitions
#include"hlist.h"

/* operator overload: << 
 * ---
 * Input:   An ostream & and a const hList &
 * Output:  None
 * Return:  An ostream
 * Time:    O(n) - Have to output all items in the hlist
 * Notes:   Allows for cout << hList by overloading the ostream operator.
 */
ostream& operator<< (ostream &ost, const hList &l)
{
    // Dummy buffer for getline
    char buffer[LIST_BUF_LEN];
    // head.next
    hList::Node *curr = l.head.next;
    // loop while curr != head
    for(int counter = INDEX_START; curr != &l.head; ++counter)
    {
        // Old Way - "1 : dictionaryword"
        // ost << counter << " : " << curr->data << endl;
        // New Way - "dictionaryword"
        ost << curr->data << endl;
        // increment curr
        curr = curr->next;
        // page at 20 lines
        if(counter % PAGER == 0)
        {
            // ost << "Continued ..." << endl; 
            // Use getline to page
            cin.getline(buffer, LIST_BUF_LEN);
        }
    }
    return ost;
}

/* alphaCheck()
 * ---
 * Input:   const char*, const char*
 * Output:  none
 * Return:  int
 * Big-O:   O(n) - Where n is the number of letters in the word.
 * Notes:   Gets the alphabetical order of two words, ala strcmp
 *          Returns -1 if foo is less than bar, 1 if it's greater,
 *          or 0 if they're the same. 
 */
int hList::alphaCheck(const char* foo, const char* bar)
{
    int rval = 0;
    size_t fooLen = strlen(foo);
    size_t barLen = strlen(bar);

    if(fooLen >= barLen)
    {
        // Loop until we either have an answer or run out of letters
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
 * Big-O:   O(n^2): This could be O(n*log(n)) if we used quicksort() 
 * Notes:   Need to make sure the hlist is in sorted alphanumerical order.
 *          Case insensitive (use tolower(char))
 */
void hList::sort(void)
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
 * Big-O:   O(1)
 * Notes:   Swaps two nodes' data.
 */
void hList::swap(Node* foo, Node* bar)
{
    char tmp[LIST_BUF_LEN];

    strncpy(tmp, foo->data, LIST_BUF_LEN);
    strncpy(foo->data, bar->data, LIST_BUF_LEN);
    strncpy(bar->data, tmp, LIST_BUF_LEN);

}


/* size()
 * ---
 * Input:   None
 * Output:  None
 * Return:  An int
 * Time:    O(1)
 * Notes:   Returns the "size" of the hlist which is the number of elements.
 */
u_int hList::size(void)
{
    return listLen; 
}


/* operator overload: []
 * ---
 * Input:   int
 * Output:  None
 * Return:  char*
 * Notes:   This returns an element of a hlist
 * Time:    O(n) - could be at the end of the hlist
 */
char* hList::operator[] (const u_int n)
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
    // if n wasn't a valid number error and exit
    else 
    {
        // Trying to access off the ass-end. Error!
        cerr << "Tried to access " 
             << n 
             << " and hlist is only of size " 
             << listLen
             << endl;
        exit(1);
    }

    return rval;
}

/* traverse()
 * ---
 * Input:   A const char*
 * Output:  none
 * Return:  Node *
 * Time:    O(n) - Could have to traverse to the end of the hlist
 * Notes:   Returns the requested position in the hList
 */
hList::Node *hList::traverse(const char* foo) const
{
    Node *curr = head.next;
    while(curr != &head && strncasecmp(curr->data, foo, strlen(foo)))
        curr = curr->next;

    return curr;
}

/* setSoundex()
 * ---
 * Input:   A const char*
 * Output:  none
 * Return:  void
 * Time:    O(1)
 * Notes:   Sets the soundex code of the hlist
 */
void hList::setSoundex(const char* foo)
{
    strncpy(soundex, foo, SOUNDEX_LEN);
    soundex[SOUNDEX_LEN] = '\0';
}


/* getSoundex()
 * ---
 * Input:   A const char*
 * Output:  none
 * Return:  void
 * Time:    O(1)
 * Notes:   Sets the soundex code of the hlist
 */
char* hList::getSoundex(void)
{
    return soundex;
}

/* insert()
 * ---
 * Input:   Two const char* (data)
 * Output:  none
 * Return:  none
 * Time:    O(nm) - n = number of words, and m = number of letters in the words
 *          This is because alphaCheck() is O(m), since it has to go through 
 *          the letters of the smaller word, and insert may have to traverse
 *          through all the words until it finds the right spot to insert it.
 *          This makes it O(n)
 * Notes:   Inserts a char* in the hlist in order. 
 */
void hList::insert(char* data)
{
    // Start insertion position with first element in hlist (head.next)
    Node *curr = head.next;

    // Advance the pointer as long as curr is not head, 
    // and curr's data is not the same data we're inserting,
    // and our data is not in alphabetical order
    while(curr != &head && 
          strncasecmp(curr->data, data, strlen(data)) &&
          alphaCheck(data, curr->data) > 0)
        curr = curr->next;

    // If it does not exist
    if(curr->data != data)
    {
        Node* tmp = new Node(curr, curr->prev, data);
        // Insert tmp like so:
        // [prev->next] ---> [tmp] <--- [next->prev]
        tmp->next->prev = tmp->prev->next = tmp; 
        ++listLen;

        // If we called sort() (which is a bubble sort) on each insert, 
        // we would end up with a time of O(n^3). This is bad.
        // sort();
    }
} 


/* remove()
 * ---
 * Input:   A const char* foo
 * Output:  none
 * Return:  A boolean
 * Time:    O(n) - could have to traverse all the nodes.
 * Notes:   Removes a char from the hlist and returns true on success.
 */
bool hList::remove(const char* foo)
{
    bool rval  = false; // Will return false if node doesn't get removed
    Node *curr = traverse(foo);
    if(curr != &head && curr->data == foo)
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        // Node successfully removed
        rval = true;    
        --listLen;
    }
    return rval;
}

/* find()
 * ---
 * Input:   A const char *
 * Output:  none
 * Return:  A char*
 * Time:    O(n) - uses traverse
 * Notes:   Returns the value for the char* if it is found,
 *          else, it returns NULL.
 */
bool hList::find(const char* foo) const
{
    bool rval = false;
    // Traverse to the position in the hList
    Node *curr = traverse(foo);
    
    // We don't care about case on soundex
    if(curr != &head && strncasecmp(curr->data, foo, strlen(foo)) == 0) 
    {
        // If this is the value we were looking for, return it.
        if(curr->data != NULL)
            rval = true;
        else
            rval = false;

    }
    // Else return NULL
    return rval;
}
        

/* empty()
 * ---
 * Input:   none
 * Output:  none
 * Return:  A boolean
 * Time:    O(1)
 * Notes:   Returns true in the event that the hlist is empty.
 */
bool hList::empty(void) const 
{ 
   return head.next == &head;   // If the hList is empty, the head will be NULL
} 

/* clear()
 * ---
 * Input:   none
 * Output:  none
 * Return:  none
 * Time:    O(n)
 * Notes:   Destructor.
 */
void hList::clear(void)
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
 * Time:    O(n) - Uses clear()
 * Notes:   Destructor.
 */
hList::~hList()
{
    clear();
} 
