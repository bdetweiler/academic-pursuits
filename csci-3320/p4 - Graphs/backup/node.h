#ifndef NODE_H
#define NODE_H
namespace node
{

template<class VertexType, class EdgeType>
class Node
{
    public:
        // The next node in the list.
        Node *next;                 
        // The previous node in the list.
        Node *prev;                 
        // The search key
        NodeType value;
        // The edge weight connecting this node to it's neighbor
        EdgeType weight;
        // Default constructor
        Node(Node *n = NULL, Node *p = NULL, VertexType v = NULL)
            : next(n), prev(p), value(v) {;;;}
};

} // namespace node
#endif
