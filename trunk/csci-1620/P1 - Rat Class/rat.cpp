// Brian Detweiler
// rat.cpp - Rat class methods

#include <iostream>
using namespace std;
//#include <iomanip>    // Used with the alternative cin method
//using std::setw;
#include "rat.h"

// input:   none 
// output:  none
// return:  none
// notes:   Default Constructor - calls set() to innitialize a rat
Rat::Rat(void)
{
    set();
}
    
// input:   Two integers 
// output:  A string error when 0 is set as the denominator
// return:  none
// notes:   Sets the object's numerator and denominator to the given values
void Rat::set(int n, int d)
{
    int a;      //
    int b;      // These are used to find the GCD
    int c;      // 

    if(d == 0) 
    {
        cerr << "Error: Divide by zero\n";
        exit(1);
    }

    // This uses a version of Euclid's GCD.
    if(n != 1 && d != 1)
    {
        a = n;
        b = d;
        while(a != 0)
        {
            c = b % a;
            b = a;      // When a == 0, b is the GCD
            a = c;
        }

        n /= b;
        d /= b;
    }

    if(n == 0)          // Zero over anything is 0/1 
        d = 1;

    if(d < 0)           // Make sure negative is in the
    {                   // numerator, not the denominator
        n *= -1;         
        d *= -1;
    }
        
    num = n;
    den = d;
}

// input:   A constant Rat reference
// output:  none
// return:  A constant Rat (the calling variable) 
// notes:   This enables the programmer to do Rat = Rat;
//          Assignment operator
Rat Rat::operator = (const Rat &r) 
{
    set(r.num, r.den);
    return *this;
}

// input:   An ostream reference and a Rat reference
// output:  none
// return:  An ostream in the format of a Rat: num/den
// notes:   Enables progammers to do cout << rat; 
ostream &operator << (ostream &ost, const Rat &r)
{
    ost << r.num << "/" << r.den;
    return ost;
}    

// input:   An istream reference and a Rat reference
// output:  none
// return:  An istream 
// notes:   Enables progammers to do cin >> rat; 
//          by storing the input values in the object's variables.
istream &operator >> (istream &ist, Rat &r)
{   
    /*
     * This is how I originally had it. This will ignore anything between two
     * ints, though I'm not entirely sure how it works. The default values for 
     * ignore() are (streamsize n = 1, and int delim = EOF). The C++
     * reference says it will extract characters until n characters have
     * been extracted or when delim is found, whichever comes first.
     * Apparently, it is smart enough to know that EOF is reached
     * when the next int starts. 
     *
     * ist >> std::setw(1) >> r.num;   
     * ist.ignore( );                  
     * ist >> std::setw(1) >> r.den;   
     * return ist;
    */

    int n, d;
    ist >> n >> d;
    r.set(n, d);
    return ist;
}    

// input:   A constant Rat reference
// output:  none
// return:  A Rat + Rat
// notes:   Enables progammers to do Rat + Rat;
Rat Rat::operator + (const Rat& r) const 
{
    Rat rval;
    rval.set(num * r.den + den * r.num, den * r.den);
    return rval;
}

// input:   A constant integer 
// output:  none
// return:  A rat
// notes:   Enables programmers to do Rat + int
Rat Rat::operator + (const int i) const 
{
    Rat tmp;
    tmp.set(i);
    return *this + tmp; // turns it into a Rat + Rat
}

// input:   A constant integer, and a constant Rat reference
// output:  none
// return:  A rat
// notes:   Enables programmers to do int + Rat
Rat operator + (const int i, const Rat &r) 
{
    return r + i;               // calls Rat + int (above)
}

// input:   none
// output:  none
// return:  A Rat reference
// notes:   PRE-Increment - Enables programmers to do ++Rat
Rat &Rat::operator ++ (void)     
{
    Rat tmp;
    Rat calling_var = *this;
    tmp.num = den;              
    tmp.den = den;            
    tmp = calling_var + tmp;    // calls Rat + Rat -> calls set() -> reduces
    num = tmp.num;              // Set *this's num to the new one
    den = tmp.den;              // Set *this's den to the new one
    return *this;               // return the calling variable as a reference
}

// input:   int (It's a HACK)
// output:  none
// return:  A Rat copy
// notes:   POST-Increment - Enables programmers to do Rat++
Rat Rat::operator ++ (int)      
{
    Rat rval = *this;           // makes a copy to return
    Rat tmp;
    tmp.num = rval.den;         
    tmp.den = rval.den;
    *this = rval + tmp;         // Now increment by den/den
    return rval;                // and return the copy
}

// input:   none
// output:  none
// return:  A Rat reference
// notes:   PRE-Decrement - Enables programmers to do --Rat
Rat &Rat::operator -- (void)    
{
    Rat tmp;
    Rat calling_var = *this;
    tmp.num = den;              
    tmp.den = den;            
    tmp = calling_var - tmp;    // calls Rat - Rat -> calls set() -> reduces
    num = tmp.num;              // Set *this's num to the new one
    den = tmp.den;              // Set *this's den to the new one
    return *this;               // return the calling variable as a reference
}

// input:   int (It's a HACK)
// output:  none
// return:  A Rat reference
// notes:   POST-Decrement - Enables programmers to do Rat--
Rat Rat::operator -- (int)      
{
    Rat rval = *this;           // makes a copy to return
    Rat tmp;
    tmp.num = rval.den;         
    tmp.den = rval.den;
    *this = rval - tmp;         // Now decrement by den/den
    return rval;                // and return the copy
}

// input:   A constant Rat reference
// output:  none
// return:  A Rat
// notes:   Enables programmers to do Rat - Rat
Rat Rat::operator - (const Rat& r) const 
{
    Rat rval;
    rval.set(num * r.den - den * r.num, den * r.den);
    return rval;
}

// input:   A constant integer
// output:  none
// return:  A Rat
// notes:   Enables programmers to do Rat - int
Rat Rat::operator - (const int i) const 
{
    Rat tmp;
    tmp.set(i);
    return *this - tmp;         // turns it into a Rat - Rat
}

// input:   A constant integer, and a constant Rat reference
// output:  none
// return:  A Rat
// notes:   Enables programmers to do int - Rat
Rat operator - (const int i, const Rat &r)
{
    return (-1*r) + i;          // call Rat + int (above)
}

// input:   A constant Rat reference
// output:  none
// return:  A Rat
// notes:   Enables programmers to do Rat * Rat
Rat Rat::operator * (const Rat& r) const 
{
    Rat rval;
    rval.set(num * r.num, den * r.den);
    return rval;
}

// input:   A constant int
// output:  none
// return:  A Rat
// notes:   Enables programmers to do Rat * int
Rat Rat::operator * (const int i) const 
{
    Rat tmp;
    tmp.set(i);
    return *this * tmp;         // turns it into a Rat * Rat
}

// input:   A constant int, and a constant Rat reference
// output:  none
// return:  A Rat
// notes:   Enables programmers to do int * Rat
Rat operator * (const int i, const Rat &r) 
{
    return r * i;               // call Rat * int (above)
}

// input:   A constant Rat reference
// output:  none
// return:  A Rat reciporocal
// notes:   Quickly get the reciporocal of a Rat
Rat Rat::reciporocal(void) const
{
    Rat tmp;
    tmp.set(den, num);
    return tmp;
}

// input:   A constant Rat reference
// output:  none
// return:  A Rat reciporocal
// notes:   Quickly get the reciporocal of a Rat
// input:   A constant Rat reference
Rat Rat::inverse(void) const
{
    return *this * -1;
}

// output:  none
// return:  A Rat
// notes:   Enables programmers to do Rat / Rat
Rat Rat::operator / (const Rat& r) const 
{
    Rat rval;
    rval.set(num * r.den, den * r.num);
    return rval;
}

// input:   A constant int
// output:  none
// return:  A Rat
// notes:   Enables programmers to do Rat / int
Rat Rat::operator / (const int i) const 
{
    Rat tmp;
    tmp.set(i);
    return *this / tmp;         // turns it into a Rat / Rat
}

// input:   A constant int, and a constant Rat reference
// output:  none
// return:  A Rat
// notes:   Enables programmers to do int / Rat
Rat operator / (const int i, const Rat &r) 
{
    Rat tmp;
    tmp.set(i);
    return tmp * r.reciporocal();               // call Rat / int (above)
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables equality tests for Rat == Rat
bool Rat::operator == (const Rat &r) const
{
    bool rval;
    Rat calling_var = *this;
    Rat arg = r;                // Will reduce the argument var


    if((calling_var.num == arg.num) && (calling_var.den == arg.den))
    {
        rval = true;
    }
    else
    {
        rval = false;
    }
    return rval;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables equality tests for Rat != Rat
bool Rat::operator != (const Rat &r) const
{
    bool rval;
    if(*this == r)
    {
        rval = false;
    }
    else
    {
        rval = true;
    }
    return rval;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables equality tests for Rat < Rat
bool Rat::operator < (const Rat &r) const
{
    bool rval;
    Rat calling_var = *this;
    Rat arg = r;                // Will reduce the argument var

    if((calling_var.num/calling_var.den) < (arg.num/arg.den))
    {
        rval = true;
    }
    else
    {
        rval = false;
    }
    return rval;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables equality tests for Rat <= Rat
bool Rat::operator <= (const Rat &r) const
{
    bool rval;
    
    if(*this == r)
    {
        rval = true;
    }
    else if(*this < r)
    {
        rval = true;
    }
    else
    {
        rval = false;
    }
    return rval;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables equality tests for Rat > Rat
bool Rat::operator > (const Rat &r) const
{
    bool rval;

    if(r < *this)
    {
        rval = true;
    }
    else
    {
        rval = false;
    }
    return rval;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables equality tests for Rat >= Rat
bool Rat::operator >= (const Rat &r) const
{
    bool rval;
    if(r <= *this)
    {
        rval = true;
    }
    else
    {
        rval = false;
    }
    return rval;
}

/* The "Laziness" operators below are just for fun,
 * not honors. Am I correct in assuming that you can't
 * do int += Rat without some kind of either static casting
 * or promotion/demotion? Left that out since I wasn't sure.
 */

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables the programmer to do Rat += Rat
Rat Rat::operator += (const Rat &r)
{
    *this = *this + r;
    return *this;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables the programmer to do Rat += int
Rat Rat::operator += (const int &i) 
{
    *this = *this + i;    // Call Rat + int
    return *this;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables the programmer to do Rat -= Rat
Rat Rat::operator -= (const Rat &r)
{
    *this = *this - r;
    return *this;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables the programmer to do Rat -= int
Rat Rat::operator -= (const int &i) 
{
    *this = *this - i;    // Call Rat - int
    return *this;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables the programmer to do Rat *= Rat
Rat Rat::operator *= (const Rat &r)
{
    *this = *this * r;
    return *this;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables the programmer to do Rat *= Rat
Rat Rat::operator *= (const int &i)
{
    *this = *this * i;
    return *this;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables the programmer to do Rat /= Rat
Rat Rat::operator /= (const Rat &r)
{
    *this = *this / r;
    return *this;
}

// input:   A constant Rat reference
// output:  none
// return:  A bool
// notes:   Enables the programmer to do Rat /= int
Rat Rat::operator /= (const int &i)
{
    *this = *this / i;
    return *this;
}

