// John W. Clark
// jclark
// Rat test program
// DO NOT modify this code

#include<iostream>
#include<cstring>
using namespace std;
#include"rat.h"         // HERE - this may be modified


void func( Rat x, Rat y );

int main()
{
    Rat x,y;

    cin >> x;
    cin >> y;
    func( x, y );

    return 0;
}

/*
 * void func( Rat x, Rat y )
 * input - two rational numbers
 * output - the results of all required operations on the rational numbers
 * return - none
 *
 * this tests the following operators :
 * assignment, +, -, *, /, both ++, both --
 * it also takes both argument by value, which tests the copy constructor
 * */
void func( Rat x, Rat y )
{
    Rat z;

    // test the basic four
    z = x + y;
    cout << x << " + " << y << " = " << z << endl;
    z = x - y;
    cout << x << " - " << y << " = " << z << endl;
    z = x * y;
    cout << x << " * " << y << " = " << z << endl;
    z = x / y;
    cout << x << " / " << y << " = " << z << endl;

    // test Rat operator int
    z = x + 4;
    cout << x << " + " << 4 << " = " << z << endl;
    z = x - 4;
    cout << x << " - " << 4 << " = " << z << endl;
    z = x * 4;
    cout << x << " * " << 4 << " = " << z << endl;
    z = x / 4;
    cout << x << " / " << 4 << " = " << z << endl;

    // test int operator Rat
    z = 3 + y;
    cout << 3 << " + " << y << " = " << z << endl;
    z = 3 - y;
    cout << 3 << " - " << y << " = " << z << endl;
    z = 3 * y;
    cout << 3 << " * " << y << " = " << z << endl;
    z = 3 / y;
    cout << 3 << " / " << y << " = " << z << endl;

    // test both increments
    cout << " x++ " << x++ << endl;
    cout << " x " << x << endl;
    cout << " ++x " << ++x << endl;
    cout << " x " << x << endl;

    // test both decrements
    cout << " y-- " << y-- << endl;
    cout << " y " << y << endl;
    cout << " --y " << --y << endl;
    cout << " y " << y << endl;

    // test comparisions
    cout << x << " == " << y << " is "
        << ( x == y ? "true" : "false" ) << endl;
    cout << x << " != " << y << " is "
        << ( x != y ? "true" : "false" ) << endl;
    cout << x << " < " << y << " is "
        << ( x < y ? "true" : "false" ) << endl;
    cout << x << " <= " << y << " is "
        << ( x <= y ? "true" : "false" ) << endl;
    cout << x << " > " << y << " is "
        << ( x > y ? "true" : "false" ) << endl;
    cout << x << " >= " << y << " is "
        << ( x >= y ? "true" : "false" ) << endl;
}
