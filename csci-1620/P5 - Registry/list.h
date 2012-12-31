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
                Word name;
                // The associative data
                Word value; 
                // Default constructor
                Node(Node *n = 0, Node *p = 0, Word nm = NULL, Word v = NULL)
                    : next(n), prev(p), name(nm), value(v) {;;;}
        }; // end class Node

        // Default constructor
        List::List(void) 
            :head(&head, &head, "", "") {;;;}
        // Destructor
        ~List();
        // Insert a node
        void insert(const Word&, const Word&);
        // Remove a node
        bool remove(const Word&);
        // Find a node
        Word find(const Word&) const;
        // Empty a node
        bool empty() const;
        // Return the pointer to where a node can be inserted
        List::Node *traverse(const Word&) const;
        // Ostream overload
        friend ostream &operator << (ostream&, const List&);
        // This now takes two Words (name and value), and is a binary
        // method. It must therefore be declared a friend. 
    private:
        // The head node
        Node head; 

}; // End class List
#endif
