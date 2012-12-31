
#include<iostream>
using namespace std;
#include"list.h"

void read ( List & a );
void func ( const List & a, const List & b );

int main()
{

    List a;
    read( a );
    cout << "set a = " << a << endl;
    List b;
    read( b );
    cout << "set b = " << b << endl;
    func( a, b );

    return 0;
}

/*
 * input: a list to read a line of input into
 * output: none
 * return: none
 * notes: the list requires the += operator to insert new items
 */
void read ( List & a )
{
    char ch;
    int data;
    while ( cin.get(ch) && ch != '\n' )
    {
        if ( !isspace ( ch ) )
        {
            cin.putback(ch);
            cin >> data;
            a += data;
        }
    }
}

/*
 * input: two lists to do operations on
 * output: the results of the operations
 * return: none
 * notes: the lists require stream extraction, |, &, -, 
 * copy construction, and assignment
 */
void func ( const List & a, const List & b )
{
    // get the union
    List result = ( a | b );
    cout << "a | b = " << result << endl;

    // get the intersection
    result = ( a & b );
    cout << "a & b = " << result << endl;

    // get the difference both ways
    result = ( a - b );
    cout << "a - b = " << result << endl;
    result = ( b - a );
    cout << "b - a = " << result << endl;
}

