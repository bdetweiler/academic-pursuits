
/*
 * John W. Clark
 * util.h
 */
#ifndef UTIL_H
#define UTIL_H

#define CHAR_BITS 8
#define U_SHORT_BITS 16
#define HEX_LEN 5

// For hash check
typedef unsigned long int   ub4;

typedef unsigned int        u_int;
typedef unsigned short      u_short;
typedef unsigned char       u_char;


u_char hashish(const u_char);

// Binary string to char
char stringToChar(const string&);

// char to binary string
string charToString(char);

// Decimal number to binary string
string decToBin(u_short, u_short = 0);

// Render non-printables printable(ASCII: 0-27, and 127)  
char* printUchar(const u_char);

#endif
