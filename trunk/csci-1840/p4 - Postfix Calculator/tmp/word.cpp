#include<cstring>
#include<iostream>
using namespace std;
#include"word.h"


/* Input:   none
 * Output:  none
 * Returns: none
 * Notes:   Default constructor: Allows for Word word;
 */
Word::Word(void)
{
    this->length  = 0;
    this->data    = new char[1];
    this->data[0] = '\0';
}

/* Input:   A const char *
 * Output:  none
 * Returns: none
 * Notes:   Copy constructor: Allows for Word word = "foo";.
 */
Word::Word(const char * cp)
{ 
    if(!cp)
    {
        this->length  = 0;
        this->data    = new char[1];
        this->data[0] = '\0';
    }
    else
    {
        this->length  = strlen(cp) + 1;
        this->data = new char[this->length];
        strcpy(this->data, cp);
    }
}

/* Input:   A const char *
 * Output:  none
 * Returns: none
 * Notes:   Copy constructor: Allows for Word word = OtherWord;
 */
Word::Word(const Word & other)
{
    this->length = other.length;
    this->data   = new char [length + 1];
    strcpy(this->data, other.data);
}

/* Input:   none
 * Output:  none
 * Returns: none
 * Notes:   Destructor
 */
Word::~Word ()
{
    delete [] this->data;
}

/* Input:   A const char *
 * Output:  none
 * Returns: A Word reference
 * Notes:   Assignment operator: Allows for word = "foo";
 */
Word & Word::operator = (const char * cp)
{
    if(!cp)
    {
        delete []this->data;
    }
    else
    {
        delete []this->data;
        this->length  = strlen(cp) + 1;
        this->data = new char[this->length];
        strcpy(this->data, cp);
    }
    return *this;
}
        
/* Input:   A const Word &
 * Output:  none
 * Returns: A Word reference
 * Notes:   Assignment operator: Allows for word = otherWord;
 */
Word & Word::operator = (const Word & other)
{
    if (this == & other)
        return * this;
    if (this->length != other.length)
    {
        delete [] this->data;
        this->length = other.length;
        this->data   = new char[this->length + 1];
    }
    strcpy (this->data, other.data);
    return * this;
}

/* Input:   A const char *
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word == otherWord);
 */
bool Word::operator == (const Word & other) const
{
    return(strcasecmp(this->data, other.data) == 0);
}

/* Input:   A const char *
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word != otherWord);
 */
bool Word::operator != (const Word & other) const
{
    return(!(*this == other));
}

/* Input:   A const char *
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word < otherWord);
 */
bool Word::operator < (const Word & other) const
{
    return(strcasecmp(this->data, other.data) < 0);
}

/* Input:   A const char *
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word > otherWord);
 */
bool Word::operator > (const Word & other) const
{
    return(strcasecmp(this->data, other.data) > 0);
}

/* Input:   A const char *
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word <= otherWord);
 */
bool Word::operator <= (const Word & other) const
{
    return(strcasecmp(this->data, other.data) <= 0);
}

/* Input:   A const char *
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word >= otherWord);
 */
bool Word::operator >= (const Word & other) const 
{
    return(strcasecmp(this->data, other.data) >= 0);
}

/* Input:   An ostream & and a const Word &
 * Output:  none
 * Returns: An ostream
 * Notes:   Ostream overload: Allows for cout << word;
 */
ostream & operator << (ostream & outs, const Word & w)
{
    outs << w.data;
    return outs;
}
