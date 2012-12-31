
/*
 * driver code for the polynomial problem
 * csci 1620
 */
#include<iostream>
using namespace std;
#include"poly.h"

void read_poly( Poly & );

int main()
{
    Poly a,b,c;
    read_poly( b );
    read_poly( c );

    a = b + c;
    cout << a << " = " << b << " + " << c << endl;
    a = b - c;
    cout << a << " = " << b << " - " << c << endl;
    a = b * c;
    cout << a << " = " << b << " * " << c << endl;

    return 0;
}

/*
 * input : the polynomial you want set
 * output : none
 * return : none, the input is by reference
 * notes : this reads input from cin until the newline
 *          adding each term to the input polynomial
 *          using the Poly += Term operator
 */

void read_poly( Poly & p )
{
    Term t;
    char ch, var;
    int coef, exp;
    while ( ( ch = cin.get() ) && ( ch != '\n' ) )
    {
        if ( ch == '+' )
        {
            cin >> coef >> var >> exp;
            t.set ( coef, var, exp );
            p += t;
        }
        else if ( ch == '-' )
        {
            cin >> coef >> var >> exp;
            t.set ( -1 * coef, var, exp );
            p += t;
        }
    }
}









