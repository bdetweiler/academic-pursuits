/*****************************************************************************
 * Author: Brian Detweiler                                                   *
 * Filename: tree.h                                                          *
 * Description: Header file for tree.cpp                                     *
 * ************************************************************************* */
#ifndef TREE_H
#define TREE_H

typedef unsigned short u_short;

#include<cmath>
using std::ceil;

#include<cstdio>
using std::printf;

#include<cstdlib>
#include<vector>
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

#include"util.h"

// For printing
#define SETW_LEN 6
// Hex length of a char for a string (ex: 0x123)
#define HEX_LEN 5 

// The table of codes
#ifndef TABLE_SIZE
#define TABLE_SIZE 256
#endif

#define CHAR_BITS 8
#define HEX_LEN 5 

// Error code for mis-matched keys
#define BADKEY 777

// Declared and set in huffman.cpp
extern bool verbose;
extern bool debug;

#define VERBOSE  if(verbose)
#define DEBUG   if(debug)

class Tree
{
    private:
        // Node inner class
        class Node
        {
            public:
                /* The isChild flag is because of the merge() method.
                 * Trees are merged by having one tree point to another's root.
                 * This causes problems with the default destructor. 
                 * So by using a flag, we just tell the destructor to leave it
                 * alone until it finds an actual root node. Then it can
                 * go to down and chop it all down.
                 */
                // Huffman-specific frequency
                u_short freq;

                // The character, if it holds one
                u_char data;

                char direction;
                
                // Parent pointer. If it's null, we have a root node.
                Node* par;
                Node* left;
                Node* right;

                // Default Constructor
                Node(u_short f = 0, u_char d = '\0', char dir = '\0')
                {
                    freq = f;
                    data = d;
                    direction = dir;

                    par = NULL;
                    left = NULL;
                    right = NULL;
                }
        };

    private:
        // Chops down the tree (used for deleting the tree)
        void chop(Node*);

        // Pad size for binary code representation of tree
        size_t codePadSize;

        // Hash key and value
        u_char key;
        u_char value;

        // Keep track of the tree size
        size_t treeSize;

        // Print the tree on its side
        void print(Node*, int, ostream&) const;

        // Our root element
        Node* root;

        // Keep track of the largest frequency.
        u_short max_freq;

        // A vector of string* to hold the codes accessable by requesting
        // the the position of the vector at the char.
        vector<string*> table;

    public:
        void clear(void);

        // Default constructor
        Tree(void);
      
        // Return the size of the binarized tree
        size_t binSize(void);

        // Constructor for Tree t = new Tree(10, 't');
        Tree(u_short, u_char);

        // Build the code for the given u_char
        const u_char getChar(string*);

        // Get a code string from the table using a char
        string getCode(const u_char);

        const Node* getRoot(void) const;
        Node* getMRoot(void);
        bool empty(void) const;
       
        string* toBinary(void);
        string* treeToBin(const Node*, string&);

        void fromBinary(string&);
        void binToTree(Node*, string&);
        // Consider changing this to void and put string code in private
        void makeCodeTable(const Node*, string&);

        void printCodeTable(void);
        // Assignment
        
        //void operator= (Tree& t);

        // Comparison Operator Overloading
        bool operator== (const Tree&) const;
        bool operator!= (const Tree&) const;
        bool operator< (const Tree&) const;
        bool operator> (const Tree&) const;
        bool operator<= (const Tree&) const;
        bool operator>= (const Tree&) const;

        
        // Merge two trees into one
        Tree* merge(Tree&);

        const u_short getMaxFreq(void);

        // Destructor
        ~Tree(void);

        // Ostream overload
        friend ostream& operator<< (ostream&, const Tree &);
};
#endif
