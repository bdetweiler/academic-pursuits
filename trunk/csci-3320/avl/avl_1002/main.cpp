
#include<iostream>
using namespace std;
#include"tree.h"

int main()
{
    Tree t;
    char op;
    int num;

    while ( cin >> op >> num )
    {
        switch( op )
        {
            case 'i':
                t.insert( num );
                break;
            case 'r':
                t.remove( num );
                break;
            case 'f':
                cout << "find for " << num << " returns "
                    << ( t.find( num ) ? "true" : "false" )
                    << endl;
                break;
            case 'p':
                cout << t << endl;
                break;
        }
    }

    return 0;
}
