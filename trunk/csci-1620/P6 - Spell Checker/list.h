/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    list.h                                                          *
 * Use:     Header definition for the List class. A list allows dynamic     *
 *          data storage. This list stores data of type Word.               *
 ***************************************************************************/
#ifndef LIST_H
#define LIST_H

#include<iostream>
using namespace std;

#include"word.h" 

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
                Word data;
                // Default constructor
                Node(Node *n = 0, Node *p = 0, Word d = NULL)
                    : next(n), prev(p), data(d) {;;;}
        }; // end class Node

        // Default constructor
        List::List(void) 
            :head(&head, &head, "") {count = 0;}
        // Destructor
        ~List();
        // Insert a node
        void insert(const Word&);
        // Remove a node
        bool remove(const Word&);
        // Find a node
        bool find(const Word&) const;
        // Empty a node
        bool empty() const;
        // Indexing overloads
        const Word & operator [] (const int) const;
        // Return the pointer to where a node can be inserted
        List::Node *traverse(const Word&) const;
        int size(void);
        // Ostream overload
        friend ostream &operator << (ostream&, const List&);
    private:
        // The dummy head node
        Node head; 
        int count;

}; // End class List
#endif
