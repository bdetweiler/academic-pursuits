#include"vertex.h"

void Vertex::set(int foo)
{
    value = foo;
}

Vertex::Vertex(Vertex* foo)
{
    // Copy over value
    value = foo->value;

    // Copy list of incomings
    for(size_t i = 0; i < (foo->incoming).size(); ++i)
        incoming[i] = (foo->incoming)[i];

    // Copy list of outgoings
    for(int i = 0; (foo->outgoing).size(); ++i)
        outgoing[i] = (foo->outgoing)[i];
}

Vertex::~Vertex(void)
{
    value = 0;
    incoming.clear();
    outgoing.clear();
}

bool Vertex::sink(void)
{
    bool rval = false;

    if((degree() > 0) && !outgoing.size())
        rval = true;

    return rval;
}

bool Vertex::empty(void)
{
    bool rval = true;

    if(value || incoming.size() || outgoing.size())
        rval = false;
    return rval
}

bool Vector::neighbor(Vertex* v)
{
    return (inNeighbor(v) || outNeighbor(v))
}

bool Vector::inNeighbor(Vertex* v)
{
    return incoming.find(v);
}

bool Vector::outNeighbor(Vertex* v)
{
    return outgoing.find(v);
}

int Vector::degree(void)
{
    return incoming.size() + outgoing.size();
}

void Vertex::attach(Vertex* v, const char* direction)
{
    if(strncasecmp(direction, "IN", strlen(direction)))
        incoming.insert(v);
    else if(strncasecmp(direction, "OUT", strlen(direction)))
        outgoing.outgoing(v);
    else
    {
        cerr << __PRETTY_FUNCTION__ << endl;
        cerr << "Must be direction of \"in\" or \"out\"" << endl;

        exit(INOUTERR);
    }
}

