/*****************************************************************************
 * File:        sspair.h                                                     *
 * Author:      Brian Detweiler                                              *
 * Description: This is a string/string pair. Used to hold a vertex and an   *
 *              edge, which is stored in string format.                      *
 *****************************************************************************/


#include<string>
#include<iostream>
using namespace std;

#ifndef SSPAIR_H
#define SSPAIR_H

// If SSCOMPARE value is second, we compare the second element
// If SSCOMPARE value is first, we compare the first element

#define SSCOMPARE second

// A Pair of strings, with the second being a number
class ssPair
{
    private:
        string first;
        string second;
    public:
        ssPair(string f, string s)
            : first(f), second(s)
            {;;;}

        void add(string data1, string data2)
        { 
            first = data1; 
            second = data2; 
        }

        /*
        void add(string data)
        { first = data; }
        
        void add(ssPair data)
        { second = data; }

        void set(string data)
        { first = data; }

        void set(string data)
        { first = data; }
        */
        string one(void)
        { return first; }
        
        string two(void)
        { return second; }

        bool operator> (ssPair& p)
        { return(stringToNum(SSCOMPARE) > stringToNum(p.SSCOMPARE)); }
        
        bool operator< (ssPair& p)
        { return(stringToNum(SSCOMPARE) < stringToNum(p.SSCOMPARE)); }
        
        bool operator>= (ssPair& p)
        { return(stringToNum(SSCOMPARE) >= stringToNum(p.SSCOMPARE)); }
        
        bool operator<= (ssPair& p)
        { return(stringToNum(SSCOMPARE) <= stringToNum(p.SSCOMPARE)); }
        
        bool operator== (ssPair& p)
        { return(stringToNum(SSCOMPARE) == stringToNum(p.SSCOMPARE)); }
        
        bool operator!= (ssPair& p)
        { return(stringToNum(SSCOMPARE) != stringToNum(p.SSCOMPARE)); }


        // TODO: Find out about initializers
        /*
        void clear(void)
        { 
            first = "";
            second = 0;
        }
        ~ssPair(void)
        { clear(); }
        */

};

ostream& operator<< (ostream& ost, ssPair pair)
{
    ost << pair.one() << " : " << pair.two();
    return ost;
}

#endif
