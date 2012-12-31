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

// Soundex-specific
#ifndef SOUNDEX_LEN
#define SOUNDEX_LEN 5
#endif

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
                // The search key
                char data[LIST_BUF_LEN];
                // Default constructor
                Node(Node *n = 0, Node *p = 0, char* d = NULL)
                    : next(n), prev(p)/*, data(d) */{strncpy(data, d, LIST_BUF_LEN - 1);}
        }; // end class Node

        // Default constructor
        List(void) 
            :head(&head, &head, "") {listLen = 0; memset(soundex, '\0', SOUNDEX_LEN);}
        // Destructor
        ~List();
        // Insert a node
        void insert(char*);
        // Set the soundex code for the list
        void setSoundex(const char*);
        // Get the soundex code for the list
        char* getSoundex(void);
        // Remove a node
        bool remove(const char*);
        // Clears a list completely
        void clear(void);
        // Find a node
        bool find(const char*) const;
        // Empty a node
        bool empty(void) const;
        // Indexing overloads
        const char* operator[] (const u_int) const;
        // Return the pointer to where a node can be inserted
        List::Node *traverse(const char*) const;
        size_t size(void);
        void sort(void);
        void swap(Node*, Node*);
        int alphaCheck(const char*, const char*);
        // Ostream overload
        friend ostream &operator << (ostream&, const List&);
    private:
        // The dummy head node
        Node head; 
        size_t listLen;
        // Soundex specific
        char soundex[SOUNDEX_LEN];
};
#endif
