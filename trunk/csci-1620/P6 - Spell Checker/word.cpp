/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    word.cpp                                                        *
 * Use:     Methods for the Word class. Mostly operator overloading, which  *
 *          allow for treating a word as a primative data type.             *
 ***************************************************************************/
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
        this->data    = new char[this->length];
        this->data[0] = '\0';
    }
    else    // Else, set it up as specified.
    {
        this->length  = strlen(cp) + 1;
        this->data    = new char[this->length];
        strncpy(this->data, cp, this->length);
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
    strncpy(this->data, other.data, this->length);
}

/* Input:   none
 * Output:  none
 * Returns: none
 * Notes:   Destructor
 */
Word::~Word()
{
    delete []this->data;
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
        delete []this->data;                   // Delete it's data
    }
    else
    {
        delete []this->data;
        this->length = strlen(cp) + 1;
        this->data   = new char[this->length]; // New array for assigned data.
        strncpy(this->data, cp, this->length); // Copy the data over.
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
    if(this != &other)                             // Check for self assignment
    {
        if(this->length != other.length)           // Lengths aren't the same
        {
            delete []this->data;                        // Delete this's data
            this->length = other.length + 1;            // Reset the length
            this->data   = new char[this->length];      // Allocate new memory
        }
        strncpy(this->data, other.data, this->length);  // Copy data over
    }
    return *this;
}

/* Input:   A const Word &
 * Output:  none
 * Returns: bool
 * Notes:   Comparison: Allows for if(word == otherWord);
 */
bool Word::operator == (const Word &other) const
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
ostream &operator << (ostream &outs, const Word &w)
{
    outs << w.data;
    return outs;
}

/* Input:   A const int 
 * Output:  none
 * Returns: A char &
 * Notes:   [] overload. Allows for treating a Word like a char array
 *          i.e. cout << word[2];
 */
char &Word::operator [] (const int n)
{
    // Tests if they passed an offset greater than possible 
    // i.e. length of 10, and they request word[12]; Return a blank word.
    char *rval;
    static char ch = '\0';
    if(n > this->length)
    {
        rval = &ch;
    }
    else
    {
        rval = &this->data[n];
    }
    return *rval;
}

/* Input:   A const int 
 * Output:  none
 * Returns: A const char &
 * Notes:   [] overload with constants. Allows for treating a Word like 
 *          a char array. i.e. cout << word[2];
 */
const char &Word::operator [] (const int n) const
{
    // Tests if they passed an offset greater than possible 
    // i.e. length of 10, and they request word[12]; Return a blank word.
    char *rval;
    static char ch = '\0';
    if(n > this->length)
    {
        rval = &ch;
    }
    else
    {
        rval = &this->data[n];
    }
    return *rval;
}

/* Input:   None
 * Output:  None
 * Return:  A Word
 * Notes:   Contains the algorithm for the Soundex code. Finds a 
 *          matching soundex code to suggest corrections.
 */
Word Word::Soundex(void) const
{
    Word word = *this;
    char code[40];  // Hold Soundex code
    
    char realcode[6] = "Z0000"; // final soundex code
    // Note: the == operator is case insensitive
    const static char *code1 = "BPFVbpfv";
    const static char *code2 = "CSKGJQXZcskgjqxz";
    const static char *code3 = "DTdt";
    const static char *code4 = "Ll";
    const static char *code5 = "MNmn";
    const static char *code6 = "Rr";

    // If the first letter is in the alphabet
    if(isalpha(word[0])) 
    {
        realcode[0] = toupper(word[0]); // First letter of the word
        // Loop through word until we've either hit the end or
        // filled up the soundex code
        int a = 0;  // kept out for scope
        for(; word[a] && a <=word.length ; ++a) 
        {
            // B P F V
            // Code = 1
            if(strchr(code1, word[a]))
            {
                code[a] = '1'; // Note: Number 1, not letter l
            }
            // C S K G J Q X Z
            // Code = 2
            else if(strchr(code2, word[a]))
            {
                code[a] = '2';
            }
            // D T
            // Code = 3
            else if(strchr(code3, word[a]))
            {
                code[a] = '3';
            }
            // L
            // Code = 4
            else if(strchr(code4, word[a]))
            {
                code[a] = '4';
            }
            // M N
            // Code = 5
            else if(strchr(code5, word[a]))
            {
                code[a] = '5';
            }
            // R
            // Code = 6
            else if(strchr(code6, word[a]))
            {
                code[a] = '6';
            }
            // ANYTHING ELSE
            // Code = 0 
            else
            {
                code[a] = '0';
            }
        }
        code[a] = '\0';     // NULL terminate collected code


        // Remove the doubles and zeros
        int i = 1;
        for(int f = 1; f <= 39 && code[f] != '\0' && i < 5; ++f)
        {
            if(code[f] != code[f - 1] && code[f] != '0')
            {
                realcode[i] = code[f]; // Put the actual values in realcode
                ++i;
            }
        }
    }
    Word rval = realcode; // we are returning a Word
    return rval;
}

