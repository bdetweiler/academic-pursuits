#include"list.h"

#define INOUTERR 1234



class Vertex
{
    private:
        int value;
        List incoming;
        List outgoing;

        void insertIncoming(Edge*);
        void insertOutgoing(Edge*);
        
        bool multiedged;

    public:
        bool sink(void);
        bool empty(void);
        void set(int);

        bool neighbor(Vertex*);
        bool inNeighbor(Vertex*);
        bool outNeighbor(Vertex*);

        void attach(Vertex*, const char*);
        int degree(void);

        Vertex(void) :
            value(0), incoming(0), outgoing(0) {;;;}
        Vertex(Vertex*);
        ~Vertex(void);
};
