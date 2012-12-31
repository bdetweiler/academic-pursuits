/*****************************************************************************
 * File:        suiPair.h                                                    *
 * Author:      Brian Detweiler                                              *
 * Description: This is a string/u_int pair. This is used to store where the *
 *              node (string) is sitting in the matrix (u_int).              *
 *              Could also hold a vertex and it's edge value in u_int form.  *
 *****************************************************************************/

#include<string>
#include<iostream>
using namespace std;

#ifndef SUIPAIR_H
#define SUIPAIR_H

// If SUICOMPARE value is second, we compare the second element
// If SUICOMPARE value is first, we compare the first element
#define SUICOMPARE second

class suiPair
{
    private:
        string first;
        u_int second;
    public:
        // TODO: Need to figure out the templating 
        //       with default arguments thing.
        suiPair(string f = "", u_int s = 0)
            : first(f), second(s)
            {;;;}

        void add(string data1, u_int data2)
        { 
            first = data1; 
            second = data2; 
        }

        /*
        void add(T1 data)
        { first = data; }
        
        void add(T2 data)
        { second = data; }

        void set(T1 data)
        { first = data; }

        void set(T2 data)
        { first = data; }
        */

        string one(void)
        { return first; }
        
        u_int two(void)
        { return second; }

        bool operator> (suiPair& p)
        { return(SUICOMPARE > p.SUICOMPARE); }
        
        bool operator< (suiPair& p)
        { return(SUICOMPARE < p.SUICOMPARE); }
        
        bool operator>= (suiPair& p)
        { return(SUICOMPARE >= p.SUICOMPARE); }
        
        bool operator<= (suiPair& p)
        { return(SUICOMPARE <= p.SUICOMPARE); }
        
        bool operator== (string s)
        { return(first == s); }

        bool operator== (suiPair& p)
        { return(SUICOMPARE == p.SUICOMPARE); }
        
        bool operator!= (suiPair& p)
        { return(SUICOMPARE != p.SUICOMPARE); }


        // TODO: Find out about initializers
        /*
        void clear(void)
        { 
            first = "";
            second = 0;
        }
        ~Pair(void)
        { clear(); }
        */

};

ostream& operator<< (ostream& ost, suiPair pair)
{
    ost << pair.one() << " : " << pair.two();
    return ost;
}

#endif
