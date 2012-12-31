#include"graph.h"

#if 0
void Graph::clear(void)
{
    graph.clear();
    multiedged = false;
}

Graph::Graph(bool di)
{
    directed = di;
    clear();
}

Graph::Graph(string v, bool di)
{
    clear();
 
    // Keep track of node positions with a map
    nodes.insert(make_pair(v, 0));

    graph.push_back(new vector<string*>());
    _yVECT(v).push_back(new string());

    directed = di;
}

Graph::Graph(string v1, string v2, bool di)
{
    clear();

    nodes.insert(make_pair(v1, 0));
    nodes.insert(make_pair(v2, 1));

    graph.push_back(new vector<string*>());
    graph.push_back(new vector<string*>());
    _yVECT(v1).push_back(new string());
    _yVECT(v2).push_back(new string());

    directed = di;
}


Graph::Graph(u_int e, string v1, string v2, bool di)
{
    clear();
    nodes.insert(make_pair(v1, 0));
    nodes.insert(make_pair(v2, 1));

    graph.push_back(new vector<string*>());
    graph.push_back(new vector<string*>());

    _yVECT(v1).push_back(new string(numToString(e)));
    _yVECT(v2).push_back(new string(numToString(e)));
    

    directed = di;
}

Graph::~Graph(void)
{
    clear();
    multiedged = false;
    directed = false;
}

bool Graph::find(string key)
{
    bool rval = false;
    if(nodes.find(key) != nodes.end());
        rval = true;
    return rval;
}

u_int Graph::getWeight(string v1, string v2)
{
    return stringToNum(*_xyVECT(v1, v2));
}

bool Graph::isDirected(void)
{
    return directed;
}

/*
void Graph::print(void)
{
    map<string, List*>::const_iterator i;
    for(i = graph.begin(); i != graph.end(); i++)
        cout << i->first << ' ' << i->second;
    cout << endl;
}
*/
#endif
