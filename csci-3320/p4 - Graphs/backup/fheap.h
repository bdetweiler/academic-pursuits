#include<string>
#include<iostream>
using namespace std;

#include"list.h"
//using namespace List;

typedef unsigned int u_int;
typedef unsigned long int u_long;

namespace FHeap
{

template<typename T> class FHeap;

template<typename T>
class Node
{
    public:
        T key;
        size_t degree;
        bool mark;
        bool negativeInfinity;

        Node<T>* child;
        Node<T>* leftSibling;
        Node<T>* rightSibling;
        Node<T>* par;

        Node(void)
            : child(NULL), leftSibling(NULL), rightSibling(NULL), par(NULL) {;;;}
        Node(T k)
            : key(k), child(NULL), leftSibling(NULL), rightSibling(NULL), par(NULL) {;;;}
        Node(Node*& n)
            : child(NULL), leftSibling(NULL), rightSibling(NULL), par(NULL) 
            {
                cout << "node assignment" << endl;
                key = n->key;
                mark = n->mark;
                negativeInfinity = n->negativeInfinity;
                child = n->child;
                leftSibling = n->leftSibling;
                rightSibling = n->rightSibling;
                par = n->par;
            }
        
        ~Node(void)
        {
            // Also known as rank or order,
            // this is how many children this node has.
            degree = 0;

            mark = false;
            negativeInfinity = false;

            child = NULL;
            leftSibling = NULL;
            rightSibling = NULL;
            par = NULL;
        }
};


template<typename T>
class FHeap
{
    private:

        // List of "root" nodes at this level. 
        List::List<Node<T>*> list;
        
        // How we access the heap
        List::Iterator<Node<T>*> minKey;

    public:

    FHeap(void)
        {
            list.clear();
            list.push_back(NULL);
            minKey = list.begin();
        }

    FHeap(T val)
        {
            list.clear();
            list.push_back(NULL);
            
            Node<T>* n = new Node<T>(val);

            n->leftSibling = n; 
            n->rightSibling = n; 
            n->par = n;
            n->child = n;
            
            list.push_back(n);
            minKey = list.begin() + 1;
        }
   
    // Assignment
    /*
    FHeap(FHeap& fh)
        : head(NULL), minKey(NULL) 
        {
            list.clear();
            list.push_back(head);

            n.sibling = &n; 
            n.par = &n;
            n.child = &n;
            
            list.push_back(&n);
        }
     */

    ~FHeap(void)
    {
        list.clear();
    }

    /*
     * Inserts a new node to the left of minKey and updates
     * the minKey value if necessary
     */
    void insert(T val)
    {
        Node<T>* n = new Node<T>(val);

        list.insertBefore(minKey, n);

        (*minKey)->leftSibling = n;
        n->rightSibling = (*minKey);
        
        // Update minKey if necessary
        if(val < (*minKey)->key)
            --minKey;
    }

    void merge(FHeap& fh)
    {
        typename vector<Node<T>*>::iterator iter;

        if(fh.getMin() < (*minKey)->key)
            iter = fh.getMinIter();

        list.splice(list.end(), fh);
        
        if(fh.getMin() < (*minKey)->key)
            minKey = fh.getMinIter() + list.end();    
    }

    T getMin(void)
    {
        return (*minKey)->key;
    }
    
    typename vector<Node<T>*>::iterator getMinIter(void)
    {
        return minKey;
    }
    
    vector<Node<T>*> getList(void)
    {
        return list;
    }



};
} // namespace FHeap
