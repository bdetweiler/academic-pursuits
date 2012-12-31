/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    hlist.h                                                          *
 * Use:     Header definition for the hList class. A hlist allows dynamic     *
 *          data storage. This hlist stores data of type char *.             *
 ***************************************************************************/
#ifndef LIST_H
#define LIST_H

// Where to index the hlist in terms of printing 
#define INDEX_START     2
#define LIST_BUF_LEN    256
#define PAGER           20


#include"configure.h"

#include<iostream>
using namespace std;


typedef unsigned      int  u_int;

class hList 
{
    public:
        // Inner class Node. Defines the individual pieces of the hlist.
        class Node
        {
            public:
                // The next node in the hlist.
                Node *next;                 
                // The previous node in the hlist.
                Node *prev;                 
                // The search key
                char data[LIST_BUF_LEN];
                // Default constructor
                Node(Node *n = 0, Node *p = 0, char* d = NULL)
                    : next(n), prev(p)/*, data(d) */{strncpy(data, d, LIST_BUF_LEN - 1);}
        }; // end class Node

        // Default constructor
        hList(void) 
            :head(&head, &head, "") {listLen = 0; memset(soundex, '\0', SOUNDEX_LEN);}
        // Destructor
        ~hList();
        // Insert a node
        void insert(char*);
        // Set the soundex code for the hlist
        void setSoundex(const char*);
        // Get the soundex code for the hlist
        char* getSoundex(void);
        // Remove a node
        bool remove(const char*);
        // Clears a hlist completely
        void clear(void);
        // Find a node
        bool find(const char*) const;
        // Empty a node
        bool empty(void) const;
        // Indexing overloads
        char* operator [] (const u_int);
        // Return the pointer to where a node can be inserted
        hList::Node *traverse(const char*) const;
        u_int size(void);
        int alphaCheck(const char*, const char*);
        void sort(void);
        void swap(Node*, Node*);
        // Ostream overload
        friend ostream &operator << (ostream&, const hList&);
    private:
        // The dummy head node
        Node head; 
        u_int listLen;
        // Soundex specific
        char soundex[SOUNDEX_LEN];
        // Current size of the table, wich will be a prime
        u_int table_size;
};
#endif
