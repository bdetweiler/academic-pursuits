/****************************************************************************
 * File:    soundex.cpp                                                     *
 * Author:  Brian Detweiler                                                 *
 * Use:     A spell checker that uses the Soundex algorithm and a           *
 *          hash table to map to dictionary words.                          * 
 *                                                                          *
 *          Options: -d [file]       Optional dictionary file. If no option *
 *                                   is given, it looks for the dictionary  *
 *                                   in standard locations.                 *
 ***************************************************************************/

#include"hash.h"

// C STD files
#include<ctype.h>
#include<fstream>
#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

char* soundex(const char*);
char* trim(const char*);
bool validWord(const char*);
char* clense(char*);
bool fexist(const char*);


#define BUF_LEN 2048

#define SHORT_BUF_LEN 256
#define CODE_LEN 6
                
#define ONE "bpfvBPFV"
#define TWO "cskgjqxzCSKGJQXZ"
#define THREE "dtDT"
#define FOUR "lL"
#define ONE "bpfvBPFV"
#define TWO "cskgjqxzCSKGJQXZ"
#define THREE "dtDT"
#define FOUR "lL"
#define FIVE "mnMN"
#define SIX "rR"
#define ZERO "bcdfgjklmnpqrstvxzBCDFGJKLMNPQRSTVXZ"
#define HR "hwHW"
#define CODE "123456"

#define SPACE " \f\n\r\t\v"
#define VALIDCHAR "-'"

#define DICT "/usr/share/dict/words"
#define ALT_DICT "/usr/share/dict/american-english"

#include<ctime>
int main(int argc, char** argv)
{
    Hash hash;
    char dict[SHORT_BUF_LEN] = {DICT};
    FILE* fp;
    char* buf = NULL;
    char* str1;
    char* token;
    size_t len = 0; 
    ssize_t read; 

    // Do verification on the dictionary file.
    if(argc == 3)
    {
        if(strcasecmp(argv[1], "-d"))
            cerr << "Usage:" << argv[0] << " [-d] [dictionary file]" << endl;
        else 
        {
            if(fexist(dict))
                strncpy(dict, argv[2], SHORT_BUF_LEN);
            else
            {
                cerr << "File " << dict << " does not exist." << endl;
                exit(1);
            }
        }
    } 
    else
    {
        if(!fexist(dict))
        {
            cerr << "File " << dict << " does not exist." << endl;
            exit(1);
        }
        else if(fexist(ALT_DICT))
            strncpy(dict, ALT_DICT, SHORT_BUF_LEN);
        else
        {
            cerr << "No dictionary found." << endl;
            cerr << "Please specify one with the -d option" << endl;
            exit(1);
        }
    }


    fp = fopen(dict, "r");

    if(fp)
    {
        // Read in dictionary and build the hash table
        while((read = getline(&buf, &len, fp)) != -1)
        {
            buf = trim(buf);
            if(validWord(buf))
                hash.insert(soundex(buf), buf);
        }
    }
    else
        cerr << "Failed to read dictionary at " << dict << endl;


    fp = fopen("/dev/stdin", "r");

    // Read from stdin
    while((read = getline(&buf, &len, fp)) != -1)
    {
        for(str1 = buf; ; str1 = NULL)
        {
            token = strtok(str1, SPACE);
            if(!token)
                break;

            // token = trim(token);
            token = clense(token);
            if(!hash.find(soundex(token), token))
            {
                cout << "Word not in dictionary: '" << token 
                     << "' code = " << soundex(token) << endl;
                cout << *hash.lookup(soundex(token));
            }
        }

    }

    return 0;
}

/* soundex()
 * ---
 * Input:   const char*
 * Output:  none
 * Return:  char*
 * Notes:   Returns a soundex code computed from the given input
 */
char* soundex(const char* foo)
{
    // foo is const, so we'll make a copy
    char word[SHORT_BUF_LEN];
    strncpy(word, foo, SHORT_BUF_LEN - 1);

    // Return value must be static since it is a pointer
    static char rval[CODE_LEN];
    // Re-initialize return value
    strncpy(rval, "Z0000", CODE_LEN - 1);

    // If the first character is alpha
    if (isalpha(word[0]))
    {
        char code[SHORT_BUF_LEN] = "";

        code[0] = toupper(word[0]);

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
    }

    return rval;
}

/* trim()
 * ---
 * Input:   const char*
 * Output:  none
 * Return:  char*
 * Notes:   Trims whitespace off of the front and back of words.
 */
char* trim(const char* proc_name)
{
    // For now, we're only going with a SHORT_BUF_LEN sized array
    // TODO: Make this a dynamic array.
    static char rval[SHORT_BUF_LEN] = ""; 
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

/* validWord()
 * ---
 * Input:   const char*
 * Output:  none
 * Return:  bool
 * Notes:   There are non-ascii characters in the standard dictionary, 
 *          which consist of umlouts and other special characters.
 *          These tend to screw things up, so we're just skipping them.
 */
bool validWord(const char* foo)
{
    bool rval = true;
    for(u_int i = 0; i < strlen(foo); ++i)
    {
        // If the current char is not an ascii character,
        // Or if it's not an alphabetical or numerical character
        // (exception: hyphen - and apostrophe ')
        // Then the word is not a valid word
        if(!isascii(foo[i]) || (!isalnum(foo[i]) && !strchr(VALIDCHAR, foo[i])))
        {
            rval = false;
            break;
        }
    }
    return rval;
}

/* clense()
 * ---
 * Input:   char*
 * Output:  none
 * Return:  char*
 * Notes:   Clenses a word of extraneous characters, such as "., etc.
 *          It leaves apostrophes and hyphens in place.
 */
char* clense(char* foo)
{
    static char tmp[BUF_LEN]; 
    memset(tmp, BUF_LEN, '\0');
    u_int j = 0;
    for(u_int i = 0; i < strlen(foo); ++i)
    {
        if(isalnum(foo[i]) || strchr(VALIDCHAR, foo[i]))
        {
            tmp[j] = foo[i];
            ++j;
        }
    }
    tmp[j] = '\0';
   
    return tmp;
}

/* fexist()
 * ---
 * Input:   char*
 * Output:  none
 * Return:  bool 
 * Notes:   This just checks that a file exists before we try to open it. 
 *          I feel like this should have been included along with 
 *          fopen and fclose. But that's just me.
 */
bool fexist(const char* path)
{
    bool rval = false;
    FILE* fp;
    fp = fopen(path, "r");
    if(fp)
    {
        rval = true;
        fclose(fp);
    }
    return rval;
}

