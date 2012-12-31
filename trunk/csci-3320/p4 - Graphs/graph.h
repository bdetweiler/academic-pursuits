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

// Node, Node Position
#include"suipair.h"

// Node, Edge
#include"sspair.h"

// Node, Node, Edge
#include"triplet.h"

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

// Returns the position of the node given a node name string
#define NODE_POS(X) nodesList.findNode(X)
// Returns a string of the node name
#define NODE(X) (*(nodesList[X])).one()

/* vType is probably going to be an int
 * eType will probably be a string
 */
template<class vType, class eType>
class Graph : public brd::Matrix<vType, eType>
{
    private:

        // Keeps a list of the nodes paired with their position in the matrix
        // for easy lookup.
        brd::cVector<suiPair*> nodesList;

        // Matrix to show graph connectivity 
        // It holds the weights
        brd::Matrix<vType, eType> matrix;

        // Heap of edges in the form of (node)---(weight)---(node)
        Heap<Triplet*> edgeHeap;

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
              {     
                    numEdges = 0; 
                    init(""); 
              }

        void init(const eType& val)
        { matrix.init(val); }

        void make_node(const string val)
        { 
            // So we know how to pad the cells when we print the matrix
            // if(val.size() > printCellSize)
                // printCellSize = val.size();

            // Pair holds value and it's position in the list
            nodesList.push_back(new suiPair(val, static_cast<u_int>(nodesList.size())));  

            // from Matrix: initRow(size_type r, TITLE_TYPE title = "")
            matrix.initRow(NODE_POS(val), val);
            matrix.initCol(NODE_POS(val), val);
        }

        void connect(const vType& v1, const vType& v2, const eType& weight)
        {
            // If the nodes don't exist, create it
            if(nodesList.findNode(v1) == -1)
                make_node(v1);

            if(nodesList.findNode(v2) == -1)
                make_node(v2);

            /*
            if(numToString(weight).size() > printCellSize)
                printCellSize = numToString(weight).size();
             */
            
cout << "if " << stringToNum(matrix[NODE_POS(v1)][NODE_POS(v2)]) <<
        " < " << stringToNum(weight) << endl;
            // Only increase the number of edges if we aren't
            // overwriting a value


            if(matrix.cellEmpty(NODE_POS(v1), NODE_POS(v2)))
            {
                /* We insert the value in the matrix at the the ij-th 
                 * (and likewise, the ji-th) position, and that officially 
                 * "connects the nodes", by adding the weight between them.
                 */
                matrix.insert_at(NODE_POS(v1), NODE_POS(v2), weight);
                matrix.insert_at(NODE_POS(v2), NODE_POS(v1), weight);
                ++numEdges;
            }
            else if(stringToNum(matrix[NODE_POS(v1)][NODE_POS(v2)]) > 
                    stringToNum(weight))
            {

                /* We insert the value in the matrix at the the ij-th 
                 * (and likewise, the ji-th) position, and that officially 
                 * "connects the nodes", by adding the weight between them.
                 */
                matrix.insert_at(NODE_POS(v1), NODE_POS(v2), weight);
                matrix.insert_at(NODE_POS(v2), NODE_POS(v1), weight);
            }
        }

        const size_t getPrintCellSize(void)
        { return printCellSize; }

        const brd::Matrix<vType, eType>& getMatrix(void)
        { return matrix; }
       
        void print(void)
        { cout << matrix << endl; }

        /*
        map<vType, u_int>& getNodes(void)
        { return nodes; }
        */

        brd::cVector<suiPair>& getNodesList(void)
        { return nodesList; }

        size_t getNumEdges(void)
        { return numEdges; }
        
        size_t getNumVertices(void)
        { return nodesList.size(); }

        eType getEdge(vType v1, vType v2)
        { return matrix[NODE_POS(v1)][NODE_POS(v2)]; }

        brd::cVector<ssPair*> getAdjacentEdges(vType v1)
        {

            // Heapsort the adjacent edges
            Heap<ssPair*> heap;
            brd::cVector<ssPair*> rval;

            // Put all adjacent edges in a heap 
            // and return them as a sorted vector
            for(u_int i = 0; i < matrix.colSize(); ++i)
                if(!matrix.cellEmpty(NODE_POS(v1), i))
                {
                    cout << *(new ssPair(NODE(i), matrix[NODE_POS(v1)][i])) << endl;
                    heap.insert(new ssPair(NODE(i), matrix[NODE_POS(v1)][i]));
                    cout << " done" << endl;
                }

            heap.print();

            while(!heap.empty())
                rval.push_back(heap.remove());

            return rval;
        }
      
        ssPair* getShortestEdgeOf(vType v1)
        { 
            Heap<ssPair*> heap;

            // Put all adjacent edges in a heap 
            for(u_int i = 0; i < matrix.rowSize(); ++i)
                if(!matrix.cellEmpty(i, NODE_POS(v1)))
                    heap.insert(new ssPair(NODE(i), matrix[i][NODE_POS(v1)]));

            return heap.remove();
        }
       
        // This returns a vector of all of them in sorted order.
        vector<ssPair*> getShortestEdgeOf(vType v1, bool dummy)
        {
            vector<ssPair*> rval;
            Heap<ssPair*> heap;

            // Put all adjacent edges in a heap 
            for(u_int i = 0; i < matrix.rowSize(); ++i)
                if(!matrix.cellEmpty(i, NODE_POS(v1)))
                    heap.insert(new ssPair(NODE(i), matrix[i][NODE_POS(v1)]));


            while(!heap.empty())
                rval.push_back(heap.remove());

            return rval;
        }

        /*
         * Gets the shortest edge in the graph, and returns it 
         * as an ordered triplet.
         */
        void makeShortestEdgeHeap(void)
        {
            edgeHeap.clear();

            // Put all adjacent edges in a heap 
            for(u_int i = 1; i < matrix.rowSize(); ++i)
                for(u_int j = 0; j <= i - 1; ++j)
                    if(!matrix.cellEmpty(i, j))
                        edgeHeap.insert(new Triplet(NODE(i), NODE(j), stringToNum(matrix[i][j])));
        }

        // Put the sorted edges in a list
        vector<Triplet*> getSortedEdgeList(void)
        {
            vector<Triplet*> edgeList;
            while(!edgeHeap.empty())
                edgeList.push_back(edgeHeap.remove());

            return edgeList;
        }

        /*
         * Get's the degree of a node.
         */
        size_t degree(vType v1)
        {
            size_t count = 0;
            for(size_t i = 0; i < getNumVertices(); ++i)
                if(!matrix.cellEmpty(NODE_POS(v1), i))
                    ++count;
            
            return count;
        }


        // Prim's
        vector<Triplet*> getMinSpanTree(void)
        {


            // Step 1: 
            //      Set counter i = 1
            //      Place an arbitrary vertex v1 of set V into set P
            //          Set V == nodesList
            //          P == minSpanTree;
            //      Define N = V - {v1} 
            //          N is a copy of nodesList, 
            //              and we can remove nodes from it
            //
            //      Define T = NULL;
            //          T doesn't really exist, because we're combining
            //          it with P, since P is a vector of ordered triplets.
            

            /*       (b)        (c)
             *     5 / \ 4      /
             *     (a)  \      /
             *          (e)   /
             *       2 / |   /3
             *       (d) |1 /
             *           | /
             *      2    |/
             *  (f)----(g)
             *
             * Initialization:
             *      i = 1;
             *      minSpanTree = {a};
             *      nodesListCopy = {b, c, d, e, f, g};
             * First Iteration:
             *      i = 2;
             *      minSpanTree = {a, b};
             *      nodesListCopy = {c, d, e, f, g};
             * Second Iteration:
             *      i = 3;
             *      minSpanTree = {a, b, e};
             *      nodesListCopy = {c, d, f, g};
             * Third Iteration:
             *      i = 4;
             *      minSpanTree = {a, b, e, g};
             *      nodesListCopy = {c, d, f};
             * Fourth Iteration:
             *      i = 5;
             *      minSpanTree = {a, b, e, g, d};
             *      nodesListCopy = {c, f};
             * Fifth Iteration:
             *      i = 6;
             *      minSpanTree = {a, b, e, g, d, f};
             *      nodesListCopy = {c};
             * Sixth Iteration:
             *      i = 7;
             *      minSpanTree = {a, b, e, g, d, f, c};
             *      nodesListCopy = {};
             */
           
            /*
             * INITIALIZATION
             */

            
            vector<Triplet*> minSpanTree;
            brd::cVector<suiPair*> nodesListCopy = nodesList;
                
            // Find the shortest edge for that vertex
            // vector<ssPair*> sortedEdges;

            // ssPair* v2 = NULL;
          
            // Get the list of shortest edges of the current node
            // sortedEdges = getShortestEdgeOf(v1, true);
                
            // Grab an arbitrary vertex
            string v1 = (*nodesListCopy[0]).one();
        
            // Push the vertex onto the set
            //      minSpanTree = {a};
            minSpanTree.insert(minSpanTree.begin(), (new Triplet(v1)));
            
            // Remove it from the list
            //      nodesListCopy = {b, c, d, e, f, g}
            nodesListCopy.erase(nodesListCopy.begin());

cout << "Just befor the for loop" << endl;            
            for(u_int i = 1; i <= getNumVertices() - 1 && !nodesListCopy.empty(); ++i)
            {

cout << "beginning of for" << endl;
                // Sort all adjacent edges
                makeShortestEdgeHeap();
              
                // Get a list of the sorted edges
                vector<Triplet*> sortedEdgeList = getSortedEdgeList();
                /* Go through all the sorted shortest edges, and see if we 
                 * can find one that has one node in nodesListCopy and one
                 * in minSpanTree
                 */
cout << "got sorted edge list:" << endl;
                for(u_int j = 0; j <= sortedEdgeList.size(); ++j)
                {
                    bool flag = true;

                    /* First we compare the first node in the edge to
                     * all the nodes in nodesListCopy. If there is a 
                     * match, then we need to find the second node in minSpanTree;
                     * EXAMPLE:
                     *      sortedEdgeList[0] == (a, b, 5)
                     *      minSpanTree == {a}
                     *      nodesListCopy == {b, c, d, e, f, g}
                     *
                     *      if((*sortedEdgeList[0]).one() == (*minSpanTree[0]).one())
                     *      {
                     *          (*minSpanTree[0]).setTwo((*sortedEdgeList[0]).two());
                     *          (*minSpanTree[0]).setThree((*sortedEdgeList[0]).three());
                     *
                     *      }
                     */
                    for(u_int k = 0; k <= nodesListCopy.size(); ++k)
                    {
cout << "a" << endl;
cout << (*sortedEdgeList[j]) << " == " << (*nodesListCopy[k]) << endl;
                        if((*sortedEdgeList[j]).one() == (*nodesListCopy[k]).one())
                        {
cout << "b" << endl;
                            for(u_int l = 0; l <= minSpanTree.size(); ++l)
                            {
cout << "c" << endl;
                                if((*sortedEdgeList[j]).two() == (*minSpanTree[l]).one())
                                {
cout << "d" << endl;
                                    (*minSpanTree[0]).setOne((*sortedEdgeList[j]).one());
cout << "e" << endl;
                                    (*minSpanTree[0]).setTwo((*sortedEdgeList[j]).two());
cout << "f" << endl;
                                    (*minSpanTree[0]).setThree((*sortedEdgeList[j]).three());
cout << "g" << endl;
                                    j = sortedEdgeList.size();
cout << "h" << endl;
                                    k = nodesListCopy.size();
cout << "i" << endl;
                                    l = minSpanTree.size();
cout << "j" << endl;
                                    flag = false;

                                    nodesListCopy.erase(nodesListCopy.begin() + k);
cout << "k" << endl;
                                }
                            }
                        }
                    }
                    // If we didn't find it in minSpanTree, 
                    // look for it in nodesListCopy
                    if(flag)
                    {
cout << "l" << endl;
                        for(u_int k = 0; k <= minSpanTree.size(); ++k)
                        {
cout << "m" << endl;
                            if((*sortedEdgeList[j]).one() == (*minSpanTree[k]).one())
                            {
cout << "n" << endl;
                                for(u_int l = 0; l <= nodesListCopy.size(); ++l)
                                {
cout << "n" << endl;
                                    if((*sortedEdgeList[j]).two() == (*nodesListCopy[l]).one())
                                    {
cout << "o" << endl;
                                        (*minSpanTree[0]).setOne((*sortedEdgeList[j]).one());
cout << "p" << endl;
                                        (*minSpanTree[0]).setTwo((*sortedEdgeList[j]).two());
cout << "q" << endl;
                                        (*minSpanTree[0]).setThree((*sortedEdgeList[j]).three());
cout << "r" << endl;
                                        j = sortedEdgeList.size();
cout << "s" << endl;
                                        k = minSpanTree.size();
cout << "t" << endl;
                                        l = nodesListCopy.size();
cout << "u" << endl;

                                        // Now remove the second one from nodesListCopy
                                        nodesListCopy.erase(nodesListCopy.begin() + l);
cout << "v" << endl;
                                    }
cout << "w" << endl;
                                }
cout << "x" << endl;
                            }
cout << "y" << endl;
                        }
cout << "z" << endl;
                    }
cout << "aa" << endl;
                }

cout << "ab" << endl;

                if(i <= getNumVertices() - 1)
                    minSpanTree.insert(minSpanTree.begin(), new Triplet());
cout << "end of for loop" << endl;
            } 

            return minSpanTree;
        }


        // Will be a list or something but void for now
#if 0        
        List::List<vType> shortestPath(vType source, vType target)
        {
            // typename map<vType, u_int>::iterator iter;
            // List::List<Pair<string, u_int>*>::iterator iter;
            // List::List<vType> S;
            // Heap<Pair<vType, u_int>*> Q;
           
            // TODO: What if we want to pass floats as the weights?
            vector<u_int> dist;
            vector<
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
#endif 
};


/* TODO: Need to make this so it checks to see if total column width 
 *       is greater than 80. If so, we need to start scrunching it
 *       down. If it starts getting too big, we'll print up to 80 chars
 *       wide, and 80 down. Then we'll page it, and print until the 
 *       last Y-axis node has been printed. Then we'll go right and
 *       start doing it over.
 */
/*
template<class vType, class eType>
inline std::ostream& operator<< (std::ostream& s, Graph<vType, eType>& g)
{
    cout << "not seg faulting" << endl;
    //s << g << endl;
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
        element = cell((*(g.getNodesList()[i])).one(), g.getPrintCellSize());
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
        s << cell((*(g.getNodesList()[i])).one(), g.getPrintCellSize(), 0, "right");
        //for(u_int k = (g.getNodesList()[i]).size(); k < g.getPrintCellSize(); ++k)
            //s << " ";

        s << "|";

        for(size_type j = 0; j < g.getNumVerticies(); ++j)
            // Print the value at this position in the matrix
            s << cell(g.getMatrix()[i][j], g.getPrintCellSize()) << " ";
    }
    
    cout << "really not seg faulting" << endl;
    s << std::endl;
    cout << "totally not seg faulting" << endl;
    return g;
}
*/
