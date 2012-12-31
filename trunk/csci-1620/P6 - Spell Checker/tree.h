/*****************************************************************************
 * Author: Brian Detweiler                                                   *
 * Filename: tree.h                                                          *
 * Description: Header file for tree.cpp                                     *
 * ************************************************************************* */

#include<iostream>
using namespace std;
#include<iomanip>
#include"word.h"
#include"list.h"

class Tree
{
    private:
        // Node inner class
        class Node
        {
            public:
                List list;
                Word data;
                Node* left;
                Node* right;
                Node(Word d = NULL)
                    : data(d), left(NULL), right(NULL) {;;;}
        };
        Node* root;
        Node* trav(const Word, Node* &) const;
    private:
        // Constructor
        Tree(const Tree &);
        // Assignment overload
        const Tree &operator = (const Tree &);
        // Chops down the tree (used for deleting the tree)
        void chop(Node*);
        // Print the tree on its side
        void print(Node*, int, ostream &) const;
    public:
        // Default constructor
        Tree(void);
        // Destructor
        ~Tree(void);
        // Insert an element in the tree
        void insert(const Word);
        // Insert a word in the tree
        void InsertWord(const Word &);
        // Index overload
        List* operator[] (const Word &); 
        // Remove an element from the tree
        void remove(const Word);
        // Find an element in the tree
        bool find(const Word) const;
        // See if the tree is empty
        bool empty(void) const;
        // Ostream overload
        friend ostream& operator<< (ostream &, const Tree &);
};
