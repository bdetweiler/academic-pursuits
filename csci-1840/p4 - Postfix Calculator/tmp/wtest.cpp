
#include<iostream>
using namespace std;
#include"word.h"


int main()
{
    Word foo1 = "test";     // constructor for char *
    cout << " foo1 = " << foo1 << endl;

    Word foo2(foo1);        // copy constructor
    cout << " foo2 = " << foo2 << endl;

    Word foo3("abc");       // constructor for char *
    cout << " foo3 = " << foo3 << endl;

    Word foo4;              // default constructor
    foo4 = "xyz";           // asignment for char *
    cout << " foo4 = " << foo4 << endl;

    Word foo5;              // default constructor
    cout << " foo5 = '" << foo5 << "'" << endl;
    foo5 = foo4;            // assignment
    cout << " foo5 = " << foo5 << endl;
    foo5 = "XYZ";           // asignment for char *
    cout << " foo5 = " << foo5 << endl;

    int fail = 0;           // counter for failures

    // basic comparision tests

    if ( foo1 == foo2 )
    {
        cout << " 1 == 2 " << endl;
    }
    else
    {
        cout << "failed test 1 "<< endl;
        ++fail;
    }

    if ( foo1 != foo3 )
    {
        cout << " 1 != 3 " << endl;
    }
    else
    {
        cout << "failed test 2 "<< endl;
        ++fail;
    }

    if ( foo3 < foo4 )
    {
        cout << " 3 < 4 " << endl;
    }
    else
    {
        cout << "failed test 3 "<< endl;
        ++fail;
    }

    if ( foo4 > foo3 )
    {
        cout << " 4 > 3 " << endl;
    }
    else
    {
        cout << "failed test 4 "<< endl;
        ++fail;
    }

    if ( foo3 <= foo3 )
    {
        cout << " 3 <= 3 " << endl;
    }
    else
    {
        cout << "failed test 5 "<< endl;
        ++fail;
    }

    if ( foo4 >= foo4 )
    {
        cout << " 4 >= 4 " << endl;
    }
    else
    {
        cout << "failed test 6 "<< endl;
        ++fail;
    }

    if ( foo3 <= foo4 )
    {
        cout << " 3 <= 4 " << endl;
    }
    else
    {
        cout << "failed test 7 "<< endl;
        ++fail;
    }

    if ( foo4 >= foo3 )
    {
        cout << " 4 >= 3 " << endl;
    }
    else
    {
        cout << "failed test 8 "<< endl;
        ++fail;
    }

    if ( foo4 == foo5 )
    {
        cout << " 4 == 5 " << endl;
    }
    else
    {
        cout << "failed test 9 "<< endl;
        ++fail;
    }

    // regression test for false positives
    const Word t1= "foo";
    const Word t2= "foo";
    if ( t1 == t2 )
    {
        cout << "test 10 ok " << endl;
    }
    if ( t1 != t2 )
    {
        cout << "failed test 10 a" << endl;
        ++fail;
    }
    if ( t1 < t2 )
    {
        cout << "failed test 10 b" << endl;
        ++fail;
    }
    if ( t1 > t2 )
    {
        cout << "failed test 10 c" << endl;
        ++fail;
    }

    // test for NULL char * construction and assignment
    Word foo = NULL;
    cout << " foo = '" << foo << "'" << endl;
    foo = NULL;
    cout << " foo = '" << foo << "'" << endl;
    cout << "passed NULL tests" << endl;

    cout << " this program failed " << fail << " test"
		<< ( fail == 1 ? "" : "s" )<< endl;


    return 0;
}
