//#include"graph.h"
#include"matrix.h"
#include"graph.h"
using namespace brd;

//#include"fheap.h"

#include"list.h"

#include<string>
#include<iostream>
#include<cstdio>
using namespace std;

#define _SPACE_ " \t\n\v\r\n"
#define BUF_LEN 256

int main(void)
{
    brd::Matrix<string, string> matrix;
    Graph<string, string> graph;
    matrix.init("");

    matrix.initRow(0);
    matrix.initRow(1);

    matrix.initCol(0);
    matrix.initCol(1);


    matrix.insert_at(0, 0, "0", "rone", "cone");
    matrix.insert_at(1, 1, "1", "rtwo", "ctwo");
    matrix.insert_at(2, 2, "2", "rthree", "cthree");
    matrix.insert_at(3, 3, "3", "rfour", "cfour");
    matrix.insert_at(4, 4, "4", "rfive", "cfive");
    
    matrix.insert_at(4, 5, "500000000", "rt", "cspan");
    cout << matrix << endl;
    matrix.insert_at(4, 5, "5", "rt", "cspan");
    cout << matrix << endl;

    matrix.clear();
    FILE* fp;
    char* buf = NULL;
    // char* str1;
    // char* token;
    size_t len = 0; 
    ssize_t read; 

    // int base = 10;
    // char* endptr;

    string pointA;
    string pointB; 
    string nodeA;
    string nodeB;
    string weight;

    fp = fopen("/dev/stdin", "r");
    
    // Read the first line from stdin which will be our path to compute
    read = getline(&buf, &len, fp);

    // Set the start and end points
    pointA = strtok(buf, _SPACE_);
    pointB = strtok(NULL, _SPACE_);
   


    // Read in adjacency list and build the graph
    int count = 0;
    while((read = getline(&buf, &len, fp)) != -1)
    {
        nodeA = strtok(buf, _SPACE_);
        nodeB = strtok(NULL, _SPACE_);
        weight = strtok(NULL, _SPACE_);

        // Build graph
        graph.connect(nodeA, nodeB, weight);
        cout << "(" << nodeA << ") ----" << graph.getEdge(nodeA, nodeB) << "----(" << nodeB << ")" << endl;

        graph.print();
        // matrix.insert_at(count, count, strtol(weight.c_str(), &endptr, base), nodeA, nodeB);
        //cout << graph << endl;
        count++;
    }



    cout << matrix << endl;

    graph.print();
    // cout << graph << endl;
    cout << "(" << nodeA << ") ----" << graph.getEdge(nodeA, nodeB) << "----(" << nodeB << ")" << endl;

    cout << "Omaha to Miami: " << graph.getEdge("Omaha", "Miami") << endl;
    cout << "NumEdges: " << graph.getNumEdges() << endl;
    cout << "NumVertices: " << graph.getNumVertices() << endl;
    brd::cVector<ssPair*> test = graph.getAdjacentEdges("Omaha");
    cout << *(test.front()) << endl;
    test.erase(test.begin());
    cout << *(test.front()) << endl;
    test.erase(test.begin());
    cout << *(test.front()) << endl;
    test.erase(test.begin());

    vector<Triplet*> stuff = graph.getMinSpanTree();
    for(u_int i = 0; i < stuff.size(); ++i)
        cout << *(stuff[i]) << endl;

    //cout << *(graph.getShortestEdge()) << endl; 
    return 0;
}
