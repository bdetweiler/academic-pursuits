/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    word.h                                                          *
 * Use:     Class definition for a Word.                                    *
 ***************************************************************************/

#ifndef WORD_H
#define WORD_H

#include <iostream>
using namespace std;
#include <cstring>

class Word
{
    public:
        // Default constructor
        Word(void);
        // Copy constructor
        Word(const char *);
        // Copy constructor
        Word (const Word &);
        // Destructor
        ~Word(void);
        // Assignment operator
        Word & operator = (const Word &);
        Word & operator = (const char *);
        // Comparison operator
        bool operator == (const Word &) const;
        bool operator != (const Word &) const;
        bool operator <  (const Word &) const;
        bool operator >  (const Word &) const;
        bool operator <= (const Word &) const;
        bool operator >= (const Word &) const;

        // Output operator
        friend ostream & operator << (ostream &, const Word &);
    private:
        int length;
        char *data;
};
#endif
