
#include<iostream>
#include<iomanip>
using namespace std;
#include"tree.h"


//Tree::Node * Tree::trav ( const int foo, Node * & par ) const 
Tree::Node * Tree::trav ( const int foo, stack<Node*> & st ) const 
{
    Node * curr = root;
    st.push ( NULL );   // this is a hack
    st.push ( NULL );
    while ( curr && curr->data != foo )
    {
        st.push ( curr );
        if ( foo < curr->data )
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr;
}

bool Tree::find ( const int foo ) const
{
    stack<Node*> st;
    Node * curr = trav ( foo, st );
    return curr;
}

void Tree::insert ( const int foo )
{
    stack<Node*> st;
    Node * curr = trav ( foo, st );
    Node * par = st.top();
    if ( !curr ) // no duplicates
    {
        curr = new Node ( foo );
        if ( !par )
        {
            root = curr;
        }
        else if ( foo < par->data )
        {
            par->left = curr;
            --par->bal;
        }
        else
        {
            par->right = curr;
            ++par->bal;
        }
        // work back up the tree
        curr = par;
        st.pop();
        par = st.top();
        while ( curr )
        {
            if ( curr->bal == 0 )
            {
                curr = NULL; // terminate
            }
            else if ( abs(curr->bal) == 1 )
            {
                // update the parent balance
                if ( !par )
                {
                    ;  // there is no parent
                }
                else if ( curr == par->left )
                    --par->bal;
                else
                    ++par->bal;
                // unwind one more level
                curr = par;
                st.pop();
                par = st.top();
            }
            else // if ( abs(curr->bal) == 2 )
            {
                rotate ( curr, par );// rotate & terminate
                curr = NULL; // terminate
            }
        }
    }
}

void Tree::rotate ( Node * curr, Node * par )
{
    Node * rval;
    // curr points a node with a +-2 balance
    if ( curr->bal > 0 )
    {
        // left
        if ( curr->right->bal > 0 )
        {
            rval = single_left( curr );// single
        }
        else
        {
            rval = double_left( curr );// double
        }
    }
    else
    {
        // right
        if ( curr->left->bal > 0 )
        {
            rval = double_right( curr );// double
        }
        else
        {
            rval = single_right( curr );// single
        }
    }
    // rval is the new root of the subtree
    if ( !par )
    {
        root = rval;
    }
    else if ( par->right == curr )
    {
        par->right = rval;
    }
    else
    {
        par->left = rval;
    }
}

Tree::Node * Tree::double_left( Node * curr )
{
    cout << __PRETTY_FUNCTION__ << endl;
    Node * child = curr->right;
    Node * gc = child->left;
    // fix the subtrees
    curr->right = gc->left;
    child->left = gc->right;
    // pointers from the new root
    gc->left = curr;
    gc->right = child;
    if ( gc->bal == 0 )
    {
        curr->bal = 0;
        child->bal = 0;
        //gc->bal = 0;
    }
    else if ( gc->bal == -1 )
    {
        curr->bal = 0;
        child->bal = 1;
        gc->bal = 0;
    }
    else //if ( gc->bal == 1 )
    {
        curr->bal = -1;
        child->bal = 0;
        gc->bal = 0;
    }
    return gc;
}
Tree::Node * Tree::double_right( Node * curr )
{
    cout << __PRETTY_FUNCTION__ << endl;
    Node * child = curr->left;
    Node * gc = child->right;
    // fix the subtrees
    child->right = gc->left;
    curr->left = gc->right;
    // pointer from new root
    gc->left = child;
    gc->right = curr;
    if ( gc->bal == 0 )
    {
        curr->bal = 0;
        child->bal = 0;
        //gc->bal = 0;
    }
    else if ( gc->bal == -1 )
    {
        curr->bal = 1;
        child->bal = 0;
        gc->bal = 0;
    }
    else // if ( gc->bal == 1 )
    {
        curr->bal = 0;
        child->bal = -1;
        gc->bal = 0;
    }
    return gc;
}

Tree::Node * Tree::single_left( Node * curr )
{
    cout << __PRETTY_FUNCTION__ << endl;
    Node * child = curr->right;
    curr->right = child->left;
    child->left = curr;
    if ( child->bal == 1 )
    {
        curr->bal = 0;
        child->bal = 0;
    }
    else
    {
        curr->bal = 1;
        child->bal = -1;
    }
    return child;
}

Tree::Node * Tree::single_right( Node * curr )
{
    cout << __PRETTY_FUNCTION__ << endl;
    Node * child = curr->left;
    curr->left = child->right;
    child->right = curr;
    if ( child->bal == -1 )
    {
        curr->bal = 0;
        child->bal = 0;
    }
    else // == 0
    {
        curr->bal = -1;
        child->bal = 1;
    }
    return child;
}

void Tree::remove ( const int foo )
{
    stack<Node*> st;
    Node * curr = trav ( foo, st );
    Node * par = st.top();

    if ( curr )
    {
        if ( curr->left && curr->right ) // 2 children
        {
            Node * rep = curr;
            par = curr;
            if ( curr->bal < 0 )
            {
                // look in the left subtree
                curr = curr->left;
                // go as far right as possible
                while ( curr->right )
                {
                    par = curr;
                    curr = curr->right;
                }
            }
            else
            {
                // look in the right subtree
                curr = curr->right;
                // go as far left as possible
                while ( curr->left )
                {
                    par = curr;
                    curr = curr->left;
                }
            }
            rep->data = curr->data;
            // foo is no longer in the tree
        }
        // we have at most 1 child
        Node * child = ( curr->left ? curr->left : curr->right );
        if ( !par )
        {
            root = child;
        }
        else if ( curr->data < par->data )
        {
            par->left = child;
            ++par->bal;
        }
        else
        {
            par->right = child;
            --par->bal;
        }
        delete curr;
        // JWC - avl changes to come
        // work back up the tree
        curr = par;
        st.pop();
        par = st.top();
        while ( curr )
        {
            if ( abs(curr->bal) == 2 )
            {
                rotate ( curr, par );// rotate
                // this decrease the height
            }
            // the previous case needs to run this too
            if ( curr->bal == 0 || abs(curr->bal) == 2 )
            {
                // update the parent balance
                if ( !par )
                {
                    ;  // there is no parent
                }
                else if ( curr == par->left )
                    ++par->bal;
                else
                    --par->bal;
                // unwind one more level
                curr = par;
                st.pop();
                par = st.top();
            }
            else // if ( abs(curr->bal) == 1 )
            {
                curr = NULL; // terminate
            }
        }
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
        ost << setw( level * OFFSET ) << n->data
            << '(' << n->bal << ')'
            << endl;
        print ( n->left, level + 1, ost );
    }
}



