/*
 * John W. Clark
 * util.cpp
 */
#include<cmath>
using std::log;
using std::ceil;

#include<iostream>
#include<iomanip>
using namespace std;

#include"util.h"

u_char hashish(const u_char key)
{
    ub4 h = 0;

    h += tolower(key);
    h += (h << 10);
    h ^= (h >> 6);

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    
    return (h % CHAR_BITS);
}


/*
 * decToBin()
 * ---
 * Input:  u_short, u_short = 0
 * Output: none
 * Return: string
 * Notes:  Converts a decimal number to binary, up to max_len bits
 */ 
string decToBin(u_short num, u_short max_len)
{
    // Default for max_len if max_len is not passed
    // Need 2 bytes to represent treeSize
    u_int max_bits = CHAR_BITS * 2;

    /* Note: If max_len is set (defaults to 0), then we want to limit
     * the length of the binary string. Other wise, we'll just
     * go with CHAR_BITS as our limit
     */
    if(max_len)
        max_bits = static_cast<u_int>(ceil(log(max_len) / log(2)));

    string rval = "";

    for(u_int i = 0; i < max_bits; ++i)
    {
        if (num & 0x01)
            rval.insert(0,"1");
        else
            rval.insert(0,"0");
        num >>= 1;
    }

    return rval;
}

/*==========================================================
 * char stringToChar(const string& s)
 * input : a string of 8 '1' or '0' characters
 * output : none
 * return : the char value for that string
 * notes : conversion code
 * =======================================================*/
char stringToChar(const string& s)
{

    char rval = 0x00;

    for ( unsigned int i = 0 ; i < CHAR_BITS ; ++i )
    {
        rval <<= 1;
        if ( i < s.length() && s[i] == '1' )
            rval |= 0x01;
    }

    return rval;
}

/*==========================================================
 * string charToString(char ch)
 * input : a character
 * output : none
 * return : the string representing the bits in the input char
 * notes : conversion code
 * =======================================================*/
string charToString ( char ch )
{
    string rval = "";
    for ( unsigned int i = 0 ; i < 8 ; ++i )
    {
        if ( ch & 0x01 )
            rval.insert(0,"1");
        else
            rval.insert(0,"0");
        ch >>= 1;
    }
    return rval;
}

/*==========================================================
 * printUchar()
 * ---
 * input:   const u_char
 * output:  none
 * return:  char*
 * notes:   Display unprintable chars in hex
 * =======================================================*/
char* printUchar(const u_char ch)
{
    static char rval[HEX_LEN] = "\0";

    if(isprint(ch) && !isspace(ch))
    {
        rval[0] = ch;
        rval[1] = '\0';
    }
    else
        snprintf(rval, HEX_LEN, "%#x", ch);
    return rval;
        //ost << "\\" << setfill('0') << oct << setw(3) 
            //<< static_cast<u_short>(ch) << dec << setfill(' ');
}

