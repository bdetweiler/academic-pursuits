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
        Word (const Word & other);
        // Destructor
        ~Word(void);
        // Assignment operator
        Word & operator = (const Word & other);
        Word & operator = (const char *);
        // Comparison operator
        bool operator == (const Word &) const;
        bool operator != (const Word &) const;
        bool operator <  (const Word &) const;
        bool operator >  (const Word &) const;
        bool operator <= (const Word &) const;
        bool operator >= (const Word &) const;

        // Output operator
        friend ostream & operator << (ostream & outs, const Word & w);
    private:
        int length;
        char *data;
};
