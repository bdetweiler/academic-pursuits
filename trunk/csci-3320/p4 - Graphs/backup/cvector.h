/****************************************************************************
 * File:    vector.h                                                        *
 * Author:  Brian Detweiler                                                 *
 * Use:     This is a checked vector class. It builds on the STL vector     *
 *          class. It basically adds bounds checking and what-not.          *
 * Source:  This code was taken from                                        *
 *                      Designing Components with the C++ STL               *
 *                      by Ulrich Breymann                                  *
 ***************************************************************************/
#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include<cassert>
#include<vector>

namespace brd
{
 // Inherets from STL's vector class
 template<class X>
 class cVector : public std::vector<X> 
 {
    public:
    typedef typename cVector::size_type size_type;
    typedef typename cVector::iterator iterator;
    typedef typename cVector::difference_type difference_type;
    typedef typename cVector::reference reference;
    typedef typename cVector::const_reference const_reference;

    cVector()
    {;;;}

    cVector(size_type n, const X& val = X()) : std::vector<X>(n, val)
    {;;;}

    cVector(iterator i, iterator j) : std::vector<X>(i, j)
    {;;;}

    reference operator[] (difference_type index)
    {
        assert(index >= 0 && 
               index < static_cast<difference_type>(this->size()));
        return std::vector<X>::operator[](index);
    }

    const_reference operator[](difference_type index) const
    {
        assert(index >= 0 &&
               index < static_cast<difference_type>(this->size()));
        return std::vector<X>::operator[](index);
    }
    
    void clear(void)
    { 
        while(!this->empty())
        {
            cout << "clear test" << endl;
            this->erase(this->begin());
        }
    }
 };

 template<class X>
 inline std::ostream& operator<< (std::ostream& s, const cVector<X>& v)
 {
    typedef typename cVector<X>::size_type size_type;

    for(size_type i = 0; i < v.size(); ++i)
    {
        s << v[i] << " ";
    }     
    s << std::endl;
    return s;
 }

} // namespace brd
#endif



        
