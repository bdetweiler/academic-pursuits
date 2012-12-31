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
                // ToDo: Will Need a Word and an int for count 
                // The data stored in the node.
                Word data;
                // The next node in the list.
                Node *next;                 
                // The previous node in the list.
                Node *prev;                 
                // This will be incremented with each duplicate Word.
                int  count; 
                // Default constructor
                Node(Word d = NULL, Node *n = 0, Node *p = 0, int c = 0)
                    : data(d), next(n), prev(p), count(c) {}
        }; // end class Node

        // Default constructor
        List();      
        // Destructor
        ~List();
        // Remove a node
        bool remove(const Word);
        // Insert a node
        void insert(const Word);
        // Find a node
        bool find(const Word) const;
        // Empty a node
        bool empty() const;
        // ToDo: write traverse()
        List::Node *traverse(const Word) const;
        // Assignment overload
        const List &operator = (const List &);  // Mine: NEW
        // Ostream overload
        friend ostream & operator << (ostream&, const List&);
    private:
        // Pointer to the head node
        Node *head; 

}; // End class List
#endif
