/*
 * misc.h
 * --
 * By Brian Detweiler
 *
 * Contains miscellaneous functions and definitions that
 * I have found useful and lacking in the C99 specification.
 */
#include<ctype.h>
// Include defenitions for file extensions
#include"extensions.h"

#ifndef BUF_LEN
#define BUF_LEN 1024
#endif

#define DICT "/usr/share/dict/words"

char* soundex(const char*);
char* trim(const char*);



/*
 * trim
 * ---
 * Input:  const char* proc_name
 * Output: 
 * Return: char*
 * Note:   Trims the whitespace off the front and back of a string
 *        
 */
char* trim(const char* proc_name)
{
    // For now, we're only going with a BUF_LEN sized array
    // TODO: Make this a dynamic array.
    static char rval[BUF_LEN] = ""; 
    u_int begin = 0;
    u_int i = 0;
    u_int j = 0;
    u_int len = strlen(proc_name);

    u_int end = len;

    // Find the beginning
    for(i = 0; i < len; ++i)
    {
        if(i == 0 && !isspace(proc_name[i]))
        {
            begin = 0;
            break;
        }
        else if(isspace(proc_name[i]))
        {
            begin = i;
            break;
        }
    }
    
    // Find the End
    for(i = len - 1; i > 0; --i)
    {
        // At the first occurance of a non-space, set the end
        if(!isspace(proc_name[i]))
        {
            end = i + 1;
            break;
        }
    }

    // Grab everything from Beginning to End
    for(i = 0, j = begin; j < len && j < end; ++i, ++j)
    {
        rval[i] = proc_name[j];
    }
    rval[i] = '\0';
    return rval;
}




/* input:   char* mainword
 * output:  None
 * return:  char*
 */
char* soundex(const char* mainword)
{
    // mainword is const, so we'll make a copy
    char word[BUF_LEN];
    strncpy(word, mainword, BUF_LEN - 1);

    // Return value must be static since it is a pointer
    static char rval[CODE_LEN];
    // Re-initialize return value
    strncpy(rval, "Z0000", CODE_LEN - 1);

    // If the first character is alpha
    if (isalpha(word[0]))
    {
        char code[BUF_LEN] = "";

        code[0] = word[0];

        int a;
        int b;

        // Build the initial code
        for(a = 1, b = 1; (word[a] != '\0'); ++a)
        {
            if(strchr(ONE, word[a]))
                code[b++] = '1';
            else if(strchr(TWO, word[a]))
                code[b++] = '2';
            else if(strchr(THREE, word[a]))
                code[b++] = '3';
            else if(strchr(FOUR, word[a]))
                code[b++] = '4';
            else if(strchr(FIVE, word[a]))
                code[b++] = '5';
            else if(strchr(SIX, word[a]))
                code[b++] = '6';
            else if(strchr(HR, word[a]))
                code[b++] = 'H';
            else
                code[b++] = '0';
        }
        
        // Null terminate
        code[b] = '\0';
        
        // Remove the doubles
        for(a = 0; code[a] != '\0'; ++a)
            if(code[a] == code[a + 1])
                code[a] = 'H';
 
        // Now put together the "real" code
        rval[0] = code[0];

        for(b = 1, a = 0; (code[a] != '\0') && (b < CODE_LEN - 1); ++a)
            if(strchr(CODE, code[a]))
                rval[b++] = code[a];
    } // end if(isalpha(word[0]))

    return rval;
}


