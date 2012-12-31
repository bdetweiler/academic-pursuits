/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    list.h                                                          *
 * Use:     Header definition for the List class. A list allows dynamic     *
 *          data storage. This list stores data of type char *.             *
 ***************************************************************************/
#ifndef LIST_H
#define LIST_H

// Where to index the list in terms of printing 
#define INDEX_START     2
#define LIST_BUF_LEN    256
#define PAGER           20

#define HEX_LEN 5
typedef unsigned short int u_short;

#define unlink(curr, rval){                                                    \
    curr->prev->next = curr->next;                                             \
    curr->next->prev = curr->prev;                                             \
    rval = curr;                                                               \
}

#include<iostream>
using namespace std;

class List 
{
    public:
        // Inner class Node. Defines the individual pieces of the list.
        class Node
        {
            public:
                // The next node in the list.
                Node *next;                 
                // The previous node in the list.
                Node *prev;                 
                // Character
                u_char data;
                // Frequency
                u_short freq;
                // Default constructor
                Node(Node* n = 0, Node* p = 0, char d = NULL, u_short f = 0)
                    : next(n), prev(p), data(d), freq(f) {;;;}
        }; // end class Node

        // Default constructor
        List(void) 
            :head(&head, &head, '\0', 0) {listLen = 0;}

        // Destructor
        ~List();

        // Insert a node
        void insert(char);
        
        // Remove a given node
        List::Node* remove(const char);
        
        // Remove the head->next node
        List::Node* remove(void);

        // Clears a list completely
        void clear(void);

        // Find a node
        bool find(const char) const;

        // Empty a node
        bool empty(void) const;

        // Indexing overloads
        const char operator[] (const u_int) const;
       
        // Returns head->next
        const List::Node* peek(void) const; 

        // Return the pointer to where a node can be inserted
        List::Node* traverse(const char) const;

        // Returns the length of the list
        size_t size(void);

        // Sort the list
        void sort(void);

        // Compare nodes to check for alphabetical order
        int alphaCheck(const char*, const char*);

        // Ostream overload
        friend ostream &operator << (ostream&, const List&);

    private:
        // The dummy head node
        Node head; 

        // Swap nodes (used for sorting)
        void swap(Node*, Node*);

        // Length of the list (accessable by list.size()).
        size_t listLen;
};
#endif
