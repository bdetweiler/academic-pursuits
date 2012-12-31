/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    word.cpp                                                        *
 * Use:     Methods for the Word class. Mostly operator overloading, which  *
 *          allow for treating a word as a primative data type.             *
 ***************************************************************************/

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
    this->length  = 1;              // Word cannot be of length 0
    this->data    = new char[1];
    this->data[0] = '\0';
}

/* Input:   A const char *
 * Output:  none
 * Returns: none
 * Notes:   Copy constructor: Allows for Word word = "foo";.
 */
Word::Word(const char *cp)
{ 
    if(!cp) // If a NULL value was entered, set up a "NULL" Word.
    {
        this->length  = 1;
        this->data    = new char[1];
        this->data[0] = '\0';
    }
    else    // Else, set it up as specified.
    {
        this->length  = strlen(cp) + 1;
        this->data    = new char[this->length];
        strcpy(this->data, cp);
    }
}

/* Input:   A const Word & 
 * Output:  none
 * Returns: none
 * Notes:   Copy constructor: Allows for Word word = otherWord;
 */
Word::Word(const Word &other)
{
    // No problem if the other word is null.
    this->length = other.length + 1;
    this->data   = new char[this->length];
    strcpy(this->data, other.data);
}

/* Input:   none
 * Output:  none
 * Returns: none
 * Notes:   Destructor
 */
Word::~Word()
{
    delete [] this->data;
}

/* Input:   A const char *
 * Output:  none
 * Returns: A Word reference
 * Notes:   Assignment operator: Allows for word = "foo";
 */
Word &Word::operator = (const char *cp)
{
    if(!cp) // If NULL
    {
        delete []this->data;                    // Delete it's data
    }
    else
    {
        delete []this->data;
        this->length = strlen(cp) + 1;
        this->data   = new char[this->length];  // New array for assigned data.
        strcpy(this->data, cp);                 // Copy the data over.
    }
    return *this;
}
        
/* Input:   A const Word &
 * Output:  none
 * Returns: A Word reference
 * Notes:   Assignment operator: Allows for word = otherWord;
 */
Word &Word::operator = (const Word &other)
{
    if(this == &other)     // Self assignment
    {
        return *this;       // Just return itself
    }
    if(this->length != other.length)                // Lengths aren't the same
    {
        delete []this->data;                        // Delete this's data
        this->length = other.length + 1;            // Reset the length
        this->data   = new char[this->length];      // Allocate new memory
    }
    strcpy(this->data, other.data);                 // Copy data over 
    return *this;                                   // Return itself
}

/* Input:   A const Word &
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word == otherWord);
 */
bool Word::operator == (const Word & other) const
{
    // Evaluate if the data is the same on the two words. 
    // It will evaluate to 0 if it is true. 
    return(strcasecmp(this->data, other.data) == 0);
}

/* Input:   A const Word &
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word != otherWord);
 */
bool Word::operator != (const Word &other) const
{
    return(!(*this == other));  // Test if addresses are the same
}

/* Input:   A const char *
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word < otherWord);
 */
bool Word::operator < (const Word &other) const
{
    // Compare the data of the two words.
    return(strcasecmp(this->data, other.data) < 0);
}

/* Input:   A const Word &
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word > otherWord);
 */
bool Word::operator > (const Word &other) const
{
    // Compare the data of the two words.
    return(strcasecmp(this->data, other.data) > 0);
}

/* Input:   A const Word &
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word <= otherWord);
 */
bool Word::operator <= (const Word &other) const
{
    // Compare the data of the two words.
    return(strcasecmp(this->data, other.data) <= 0);
}

/* Input:   A const Word &
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word >= otherWord);
 */
bool Word::operator >= (const Word & other) const 
{
    // Compare the data of the two words.
    return(strcasecmp(this->data, other.data) >= 0);
}

/* Input:   An ostream & and a const Word &
 * Output:  none
 * Returns: An ostream
 * Notes:   Ostream overload: Allows for cout << word;
 */
ostream & operator << (ostream &outs, const Word &w)
{
    outs << w.data;
    return outs;
}
