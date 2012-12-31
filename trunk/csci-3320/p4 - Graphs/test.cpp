#include"list.h"
#include"pair.h"

#include"matrix.h"
#include"cvector.h"

// #include"hash.h"

#include<string>
// #include<utility>
using namespace std;

int main(void)
{
    brd::Matrix<string, u_int> matrix;
    brd::cVector<Pair<string, u_int>*> nodeList;

    matrix.init(0);

    // brd::cVector<string> nodes;
    string nodes[4] = {"foo", "bar", "baz", "boo"};
    

    cout << nodes[0] << endl;
    cout << nodes[1] << endl;
    cout << nodes[2] << endl;
    cout << nodes[3] << endl;
    
   
    for(u_int i = 0; i <= 3; ++i)
    {
        nodeList.push_back(new Pair<string, u_int>(nodes[i], i));
        matrix.initRow(i, nodes[i]);
        matrix.initCol(i, nodes[i]);
        cout << *(nodeList[i]) << endl;
    }

    cout << "baz: = " << nodeList.findNode("baz") << endl;;
    cout << "bar: = " << nodeList.findNode("bar") << endl;;
    cout << "foo: = " << nodeList.findNode("foo") << endl;;
    cout << "boo: = " << nodeList.findNode("boo") << endl;;
    cout << "blah: = " << nodeList.findNode("blah") << endl;;

    matrix.insert_at(0, 2, 7);
    matrix.insert_at(0, 3, 10);
    matrix.insert_at(3, 1, 5);
    matrix.insert_at(2, 0, 7);
    matrix.insert_at(3, 0, 10);
    matrix.insert_at(1, 3, 5);


    cout << matrix << endl;

    List::List<Pair<string, u_int>*> list;

    Pair<string, u_int> pair1("test", 12);
    Pair<string, u_int> pair2("test", 13);
    Pair<string, u_int> pair3("best", 1);

    list.push_back(new Pair<string, u_int>("test", 12));

    cout << pair1 << endl;
    cout << list << endl;

    return 0;
}
