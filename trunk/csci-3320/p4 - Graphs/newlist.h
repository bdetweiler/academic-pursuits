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

#include"configure.h"
#include"pair.h"

#include<iostream>
using namespace std;

typedef unsigned int u_int;

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
                Pair<string, u_int> data;
                // Default constructor
                Node(Node *n = 0, Node *p = 0, string s = "", u_int ui = 0)
                    : next(n), prev(p), data(s, ui)
                    {;;;}
        }; // end class Node

        // Default constructor
        List(void) 
            :head(&head, &head, "", 0) 
            { listLen = 0; }
        // Destructor
        ~List();
        // Insert a node
        void insert(Pair<string, u_int>);
        // Set the soundex code for the list
        void setSoundex(Pair<string, u_int>);
        // Get the soundex code for the list
        char* getSoundex(void);
        // Remove a node
        bool remove(Pair<string, u_int>);
        // Clears a list completely
        void clear(void);
        // Find a node
        bool find(Pair<string, u_int>) const;
        // Empty a node
        bool empty(void) const;
        // Indexing overloads
        char* operator [](const u_int);
        // Return the pointer to where a node can be inserted
        List::Node *traverse(string) const;
        u_int size(void);
        // int alphaCheck(const char*, const char*);
        // void sort(void);
        // void swap(Node*, Node*);
        // Ostream overload
        friend ostream &operator << (ostream&, const List&);
    private:
        // The dummy head node; No data in here
        Node head; 
        u_int listLen;
};
#endif
