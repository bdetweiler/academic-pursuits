
#include<iostream>
#include<iomanip>
using namespace std;
#include"tree.h"


Tree::Node * Tree::trav ( const int foo, Node * & par ) const 
{
    Node * curr = root;
    par = NULL;
    while ( curr && curr->data != foo )
    {
        par = curr;
        if ( foo < curr->data )
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr;
}

bool Tree::find ( const int foo ) const
{
    Node * par = NULL;
    Node * curr = trav ( foo, par );
    return curr;
}

void Tree::insert ( const int foo )
{
    Node * par = NULL;
    Node * curr = trav ( foo, par );
    if ( !curr ) // no duplicates
    {
        curr = new Node ( foo );
        if ( !par )
            root = curr;
        else if ( foo < par->data )
            par->left = curr;
        else
            par->right = curr;
    }
}

void Tree::remove ( const int foo )
{
    Node * par = NULL;
    Node * curr = trav ( foo, par );
    if ( curr )
    {
        if ( curr->left && curr->right ) // 2 children
        {
            Node * rep = curr;
            // look in the left subtree
            par = curr;
            curr = curr->left;
            // go as far right as possible
            while ( curr->right )
            {
                par = curr;
                curr = curr->right;
            }
            rep->data = curr->data;
            // foo is no longer in the tree
        }
        // we have at most 1 child
        Node * child = ( curr->left ? curr->left : curr->right );
        if ( !par )
            root = child;
        else if ( curr->data < par->data )
            par->left = child;
        else
            par->right = child;
        delete curr;
    }
}

void Tree::chop ( Node * n )
{
    if ( n )
    {
        chop ( n->left );
        chop ( n->right );
        delete n;
    }
}

void Tree::print ( Node * n, int level, ostream & ost ) const
{
    static const int OFFSET = 6;
    if ( n )
    {
        print ( n->right, level + 1, ost );
        // output
        ost << setw( level * OFFSET ) << n->data << endl;
        print ( n->left, level + 1, ost );
    }
}



