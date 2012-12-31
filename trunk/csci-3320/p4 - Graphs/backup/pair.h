#include<iostream>
using namespace std;

#ifndef PAIR_H
#define PAIR_H

// If COMPARE value is second, we compare the second element
// If COMPARE value is first, we compare the first element
#define COMPARE second

template<class T1, class T2>
class Pair
{
    private:
        T1 first;
        T2 second;
    public:
        // TODO: Need to figure out the templating 
        //       with default arguments thing.
        Pair(T1 f = "", T2 s = 0)
            : first(f), second(s)
            {;;;}

        void add(T1 data1, T2 data2)
        { 
            first = data1; 
            second = data2; 
        }

        void add(T1 data)
        { first = data; }
        
        void add(T2 data)
        { second = data; }

        void set(T1 data)
        { first = data; }

        void set(T2 data)
        { first = data; }

        T1 one(void)
        { return first; }
        
        T2 two(void)
        { return second; }

        bool operator> (Pair& p)
        { return(COMPARE > p.COMPARE); }
        
        bool operator< (Pair& p)
        { return(COMPARE < p.COMPARE); }
        
        bool operator>= (Pair& p)
        { return(COMPARE >= p.COMPARE); }
        
        bool operator<= (Pair& p)
        { return(COMPARE <= p.COMPARE); }
        
        bool operator== (Pair& p)
        { return(COMPARE == p.COMPARE); }
        
        bool operator!= (Pair& p)
        { return(COMPARE != p.COMPARE); }


        // TODO: Find out about initializers
        void clear(void)
        { 
            first = "";
            second = 0;
        }

        ~Pair(void)
        { clear(); }

};

template<class T1, class T2>
ostream& operator<< (ostream& ost, Pair<T1, T2> pair)
{
    ost << pair.one() << " : " << pair.two();
    return ost;
}

#endif
