/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    graph.h                                                         *
 * Use:     Header definition for the Graph class. A graph allows dynamic   *
 *          interconnected data modelling. 
 *                                                                          *
 *          Please note that all functions that take two nodes are in the   *
 *          form of Vertex1 ----> Vertex2. This only matters if the graph   *
 *          is directed.                                                    *
 ***************************************************************************/

#include<string>
#include<map>
#include<iostream>
using namespace std;

#include"matrix.h"
#include"cvector.h"

#include"dheap.h"

#include"list.h"

#include"pair.h"

/* INFINITY is defined as a maximum unsigned int.
 * Since computers are finite state machines, we have to pick a finte number.
 * If our edge weights are approaching this number,
 * we are probably in trouble anyway, and should consider
 * using long unsigned ints
 */
#ifdef INFINITY
#undef INFINITY
#define INFINITY 4294967295
#endif

#define NODE_POS(X) nodes[X] - 1

/* vType is probably going to be an int
 * eType will probably be a string
 */
template<class vType, class eType>
class Graph : public brd::Matrix<vType, eType>
{
    private:
        // removed nodesList and nodes

        List::List<Pair<vType, eType> nodes;
        // Matrix to show graph connectivity 
        // It holds the weights
        brd::Matrix<vType, eType> matrix;

        /* Ideas for how to do nodes["Vertex1"] and get the point where the
         * node is in the Matrix. 
         *
         *  1. Do some kind of macro
         *  2. Do a custom linked list
         *  3. Overload operators in Pair so that comparison gives 
         *     us what we want
         *
         */
        /* With the above two containers, we can do this:
         *      matrix.insert_at(nodes["Vertex1"], nodes["Vertex2"], value);
         * and it will insert the weight for the edge at Vertex1 -> Vertex2
         */

        size_t numEdges;

        size_t printCellSize;

    public:

        typedef typename std::vector<eType>::size_type size_type;
        Graph(size_type x = 1, size_type y = 1, bool m = false, bool d = true)
            : brd::Matrix<vType, eType>(x, y), 
              printCellSize(0)
              { numEdges = 0; }

        void init(const eType& val)
        { matrix.init(val); }

        void make_node(const string val)
        { 
            // So we know how to pad the cells when we print the matrix
            if(val.size() > printCellSize)
                printCellSize = val.size();

            // This will allow us to do nodes[vertex] - 1 to get the position
            // of the node in the matrix. 
            nodes.insert(make_pair(val, static_cast<u_int>(nodes.size() + 1)));  

            nodesList.push_back(val);
            /* The idea here is that we have two ways of retreiving information
             * about the node position. 
             * EXAMPLE:
             *    if "node" is the third node we inserted, then
             *      nodes["node"] - 1 returns 3. We macro'd this
             *      NODE_POS("node") returns 3
             *      nodesList[3] returns "node"
             *      And therefore,
             *      nodesList[nodes["node"]] will return "node" and
             *      nodes[nodesList[3]] will return 3;
             */
            matrix.initRow(NODE_POS(val));
        }

        void connect(const vType& v1, const vType& v2, const eType& weight)
        {
            if(nodes.find(v1) == nodes.end())
                make_node(v1);

            if(nodes.find(v2) == nodes.end())
                make_node(v2);

            if(numToString(weight).size() > printCellSize)
                printCellSize = numToString(weight).size();

            matrix.insert_at(NODE_POS(v1), NODE_POS(v2), weight);
cout << "connecting " << v1 << " and " << v2 << endl;
cout << "connecting at " << NODE_POS(v1) << ", " << NODE_POS(v2) << ", " << weight << ");" << endl;
            
            ++numEdges;

            // If it's not directed, we need to connect from A to B, 
            // and from B to A.
            if(!directed)
                matrix.insert_at(NODE_POS(v2), NODE_POS(v1), weight);
        }

        const size_t getPrintCellSize(void)
        { return printCellSize; }

        const brd::Matrix<vType, eType>& getMatrix(void)
        { return matrix; }
        
        map<vType, u_int>& getNodes(void)
        { return nodes; }
        
        List::List<vType>& getNodesList(void)
        { return nodesList; }

        size_t getNumEdges(void)
        { return numEdges; }
        
        size_t getNumVerticies(void)
        { return nodesList.size(); }

        size_t degree(vType v)
        {
cout << v << " position is " << NODE_POS(v) << endl;
            size_t count = 0;
            for(size_t i = 0; i < getNumVerticies(); ++i)
            {
                cout << "matrix[" << NODE_POS(v) << "][" << i << "] = ";
                cout << matrix[NODE_POS(v)][i] << endl;
                if(matrix[NODE_POS(v)][i] > 0)
                    ++count;
            }
            return count;
        }

        // Will be a list or something but void for now
        List::List<vType> shortestPath(vType source, vType target)
        {
            //typename map<vType, u_int>::iterator iter;
            //List::List<Pair<string, u_int>*>::iterator iter;
            List::List<vType> S;
            Heap<Pair<vType, u_int>*> Q;

            List::List<Pair<string, u_int>*> dist;
            List::List<Pair<string, u_int>*> prev;

            Q.insert(new Pair<vType, eType>(nodesList[0], matrix[0][0]));
            Q.insert(new Pair<vType, eType>(nodesList[1], matrix[0][1]));
            Q.insert(new Pair<vType, eType>(nodesList[2], matrix[0][2]));

            Q.print();

cout << *Q.remove() << endl;
cout << *Q.remove() << endl;
cout << *Q.remove() << endl;

cout << "source = " << source << " and nodes[source] = " << NODE_POS(source) << endl;
            // Example:
            //dist.push_back(new Pair<vType, eType>(source, matrix[NODE_POS(source)][i]));
            
            // Initialize Single Source
            // For each vertex v in Vertices(matrix)
            for(u_int i = 0; i < nodesList.size(); ++i)
            {
                //      g.d[v] := infinity
                if(nodesList[i] == source)
                    dist.push_back(new Pair<vType, eType>(nodesList[i], 0));
                else
                    // g.d[s] = 0; 
                    dist.push_back(new Pair<vType, eType>(nodesList[i], INFINITY));

                //      g.pi[v] := nil
                prev.push_back(new Pair<vType, eType>(nodesList[i], 0));
            }

cout << "distance: \n" << dist << endl;
cout << "previous: \n" << prev << endl;
            
            //map<vType, u_int> d;
            List::List<vType> pi;

            // Q is a Priority Queue of all verticies in the matrix
            // Q := copy(matrix);
            for(u_int i = 0; i < nodesList.size(); ++i)
            {
                for(u_int j = 0; j < nodesList.size(); ++j)
                {
                    cout << "Inserting " << nodesList[i] << " Q: matrix[" << i << "][" << j << "]" << endl;
                    //Q.insert(new Pair<vType, eType>(nodesList[i], matrix[i][j]));
                    cout << "Inserted in Q" << endl;
                }
            }
                    //Q.insert(new Pair<vType, eType>(nodesList[2], matrix[0][2]));
            
            Q.print();
            // while Q is not Empty
            while(!Q.empty())
            {
                cout << *Q.remove() << endl;
                // extract_min() searches Q that has the least dist[u] value
                // The value is removed and returned to the user
                // I'm thinking Fibonacci Heap here
                // u := extract_min(Q);
                // for each(neighbor of u)
                    // alt = dist dist[u] + length(u, v);
                    // if alt < dist[v]
                        // dist[v] := alt;
                        // previous[v] := u;
            }

            // Now we can get the shortest path
            // S := empty_sequence;
            // u := target;
            // while defined prev[u]
                // insert u at beginning of S
                // u := prev[u]
            return pi;
        }
};


/* TODO: Need to make this so it checks to see if total column width 
 *       is greater than 80. If so, we need to start scrunching it
 *       down. If it starts getting too big, we'll print up to 80 chars
 *       wide, and 80 down. Then we'll page it, and print until the 
 *       last Y-axis node has been printed. Then we'll go right and
 *       start doing it over.
 */
template<class vType, class eType>
inline std::ostream& operator<< (std::ostream& s, Graph<vType, eType>& g)
{
    typedef typename Graph<vType, eType>::size_type size_type;

    typename map<vType, u_int>::iterator iter;

    string element = "";

    s << std::endl;

    // Spacing for where the first column header should start
    for(u_int i = 0; i <= g.getPrintCellSize() + 1; ++i)
        s << " ";

    // Print out the node names along the top of the matrix
    for(u_int i = 0; i < g.getNodesList().size(); ++i)
    {
        // The padding needed for each side
        //u_int padding = abs(static_cast<int>((iter->first).size() - g.getPrintCellSize())) / 2;
        //for(u_int i = 0; i < padding; ++i)
            //s << " ";
        element = cell(g.getNodesList()[i], g.getPrintCellSize());
        s << element << " ";

        //for(u_int i = 0; i < padding; ++i)
            //s << " ";
    }

    s << endl;

    // Advance to the first column header
    for(u_int i = 0; i <= g.getPrintCellSize(); ++i)
        s << " ";

    s << "__";
    // Print out an underline under the column headers
    for(u_int i = 0; i < g.getNodesList().size(); ++i)
        for(u_int j = 0; j <= g.getPrintCellSize(); ++j)
            s << "_";

    for(size_type i = 0; i < g.getNumVerticies(); ++i)
    {
        s << std::endl;

        // Print out the row header
        s << cell(g.getNodesList()[i], g.getPrintCellSize(), 0, "right");
        //for(u_int k = (g.getNodesList()[i]).size(); k < g.getPrintCellSize(); ++k)
            //s << " ";

        s << "|";

        for(size_type j = 0; j < g.getNumVerticies(); ++j)
            // Print the value at this position in the matrix
            s << cell(g.getMatrix()[i][j], g.getPrintCellSize()) << " ";
    }
    
    s << std::endl;
    return s;

}
