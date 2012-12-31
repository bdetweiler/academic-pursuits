/*****************************************************************************
 * File:        triplet.h                                                    *
 * Author:      Brian Detweiler                                              *
 * Description: This is a string/string/u_int triplet.                       * 
 *              Used to hold two vertices and an edge.                       *
 *****************************************************************************/


#include<string>
#include<iostream>
using namespace std;

#ifndef TRIPLET_H
#define TRIPLET_H

#define TRIPCOMPARE third

// A Pair of strings, with the second being a number
class Triplet
{
    private:
        string first;
        string second;
        u_int third;

    public:
        Triplet(string f = "", string s = "", u_int t = 0)
            : first(f), second(s), third(t)
            {;;;}

        void setOne(string data)
        { first = data; }
        
        void setTwo(string data)
        { second = data; }
        
        void setThree(u_int data)
        { third = data; }

        string one(void)
        { return first; }
        
        string two(void)
        { return second; }
        
        u_int three(void)
        { return third; }

        bool operator> (Triplet& t)
        { return(TRIPCOMPARE > t.TRIPCOMPARE); }
        
        bool operator< (Triplet& t)
        { return(TRIPCOMPARE < t.TRIPCOMPARE); }
        
        bool operator>= (Triplet& t)
        { return(TRIPCOMPARE >= t.TRIPCOMPARE); }
        
        bool operator<= (Triplet& t)
        { return(TRIPCOMPARE <= t.TRIPCOMPARE); }
        
        bool operator== (Triplet& t)
        { return(TRIPCOMPARE == t.TRIPCOMPARE); }
        
        bool operator!= (Triplet& t)
        { return(TRIPCOMPARE != t.TRIPCOMPARE); }

        void clear(void)
        { 
            first = "";
            second = "";
            third = 0;
        }
/*
        ~Triplet(void)
        { clear(); }
        */

};

ostream& operator<< (ostream& ost, Triplet triplet)
{
    ost << "(" 
        << triplet.one() 
        << ")--- " 
        << triplet.three() 
        << " ---(" 
        << triplet.two() 
        << ")";
    return ost;
}

#endif
