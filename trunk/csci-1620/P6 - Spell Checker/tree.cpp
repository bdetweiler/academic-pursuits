#include<iostream>
using namespace std;
#include<iomanip>
#include"tree.h"
#include"word.h"
#include"list.h"

/* Input:   A const Word, and a Node *&
 * Output:  None
 * Return:  A Node *
 * Notes:   Traverses to the desired location in the tree.
 */
Tree::Node *Tree::trav(const Word foo, Node *&par) const
{
    Tree::Node *curr = root;
    par        = NULL; // parent
    while(curr && curr->data != foo)
    {
        par  = curr;
        curr = (curr->data < foo ? curr->right : curr->left);
    }
    return curr;
}

/* Input:   None
 * Output:  None
 * Return:  None
 * Notes:   Default Constructor: allows for declaration of Tree t;
 */
Tree::Tree(void)
{
    root = NULL;
}

/* Input:   None
 * Output:  None
 * Return:  A bool 
 * Notes:   Returns true if the Tree is empty, false if it is not.
 */
bool Tree::empty(void) const
{
    return !root;
}

/* Input:   A const Word
 * Output:  None
 * Return:  A bool
 * Notes:   Lets programmer varify if a node exists
 */
bool Tree::find(const Word foo) const
{
    Node *par  = NULL;              // Parent set to NULL
    Node *curr = trav(foo, par);
    return curr;
}

/* Input:   A const Word &
 * Output:  None
 * Return:  A list *
 * Notes:   Allows for tree[n] indexing
 */
List *Tree::operator [] (const Word &word) 
{
    static List l;  // Empty dummy list for nonvalid Words
    Word soundex = word.Soundex();  // Soundex code of input word
    Node *par    = NULL;            // Parent
    Node *curr   = trav(soundex, par); 
    List *rval;
    if(!curr)   // If trav() didn't return anything
    {
        rval = &l; // Return a reference to the dummy list
    }
    else
    {
        rval = &(curr->list); // Otherwise, return a reference to the list
    }
    return rval;
}

/* Input:   A const Word &
 * Output:  None
 * Return:  None
 * Notes:   Allows for inserting a word with soundex
 */
void Tree::InsertWord(const Word &word)
{
    Word soundex = word.Soundex();
    Node *par    = NULL;
    Node *curr   = trav(soundex, par);
    if(!curr) 
    {
        curr = new Node(soundex); // Node with soundex code
        curr->list.insert(word);  // Insert the word into our list
        if(!par)                  // if par == NULL
        {
            root = curr;
        }
        else if(par->data < soundex) // If data < soundex
        {
            par->right = curr; // Insert curr on the right
        }
        else                   // if data > soundex
        {
            par->left = curr;  // Insert curr on the left
        }
    }
    else
    {
        curr->list.insert(word); // Insert word into existing list
    }

}

/* Input:   A const Word 
 * Output:  None
 * Return:  None
 * Notes:   Inserts the desired value at the right location
 */
void Tree::insert(const Word foo)
{
    Node *par = NULL;
    Node *curr;
    curr = trav(foo, par);
    if(!curr) // Find the right location
    {
        curr = new Node(foo);
        if(!par)
        {
            root       = curr;
        }
        else if(par->data < foo)
        {
            par->right = curr;
        }
        else
        {
            par->left  = curr;
        }
    }
}   // Insert

/* Input:   A const Word
 * Output:  None
 * Return:  None
 * Notes:   Removes the selected element if it exists
 */
void Tree::remove(const Word foo)
{
    Node *par  = NULL;
    Node *curr = trav(foo, par);
    if(curr)                            // if it exists
    {
        if(curr->left && curr->right)   // if it has 2 children
        {
            Node *rep = curr;           // value to replace
            par       = curr;           
            curr      = curr->left;
            while(curr->right)
            {
                par  = curr;
                curr = curr->right;
            }
            rep->data = curr->data;
        }   // At this point, parent has, at most, one child.
        // This points to the one remaining child if it is there
        Node *child = (curr->left ? curr->left : curr->right);
        if(!par)
        {
            root = child;
        }
        else if(par->data < curr->data)
        {
            par->right = child;
        }
        else    // covers > and ==
        {
            par->left = child;
        }
        delete curr;
    } // if(curr)
} // remove

/* Input:   A Node *
 * Output:  None
 * Return:  None
 * Notes:   Fuck the Rain Forrest! Chop the Tree down starting at the root.
 */
void Tree::chop(Node *n)
{
    if(n)
    {
        chop(n->left);  // Recursive function: Chops left then right
        chop(n->right); //      all the way down the tree. 
        delete n;       // Will finally delete the last node here.
    }
}

/* Input:   None
 * Output:  None
 * Return:  None
 * Notes:   Destructor: Deletes the Tree when it goes out of scope
 */
Tree::~Tree(void)
{
    chop(root);
}

/* Input:   A Node *, an int, and an ostream
 * Output:  The Tree's structure using the elements and setw()
 * Return:  None
 * Notes:   Prints the Tree out sideways using the nodes of the tree
 *          (recursively) and setw() formatting.
 */
void Tree::print(Node *n, int level, ostream &ost) const
{
    if(n)
    {
        print(n->right, level + 1, ost);
        ost << setw(6 + level) << n->data << endl;
        print(n->left, level + 1, ost);
    }
}

/* Input:   An ostream, and a const Tree &
 * Output:  None
 * Return:  An ostream
 * Notes:   Allows for cout << Tree;
 */
ostream &operator << (ostream &ost, const Tree &t)
{
    t.print(t.root, 1, ost);
    return ost;
}
