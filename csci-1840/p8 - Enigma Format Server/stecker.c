/*
 * Enigma v 2.0
 * --
 * stecker.c
 * by Brian Detweiler
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"stecker.h"

#define BUG   2   // Change to 0 to turn on debugging 
#define DEBUG 1  
#define TRACEF(x)       if ( DEBUG >= (x) )

/*
 * stecker_init()
 * --
 * Input:   Stecker*, char*
 * Output:  None
 * Return:  None
 * Notes:   The idea here is to take in the input
 *          from the command line, which assigns
 *          letters to swap. So we swap them in the 
 *          alphabet, much like the reflectors. Then
 *          in the encrypt function, it will just be
 *          a 1:1 mapping.
 */
void stecker_init(Stecker* s, char* swapMe)
{
    TRACEF(BUG) printf("stecker.c: "
                       "stecker_init(): "
                       "Begin initialization\n");

    char  alphabet[] = ALPHABET;
    char* word;
    if(swapMe)
    {
        word = malloc(strlen(swapMe) * sizeof(char));
        assert(word);
    }

    /*
     * Too many parings?
     */
    if(strlen(swapMe) > ALPHALEN + 13)
        error("stecker", "stecker_init", 
              "Too many stecker pairings.");
    /*
     * Our Swap function pointer
     */
    s->steckerSwap   = stecker_encrypt;
    s->lookup        = findCharNum;

    strncpy(s->alphabet, ALPHABET, ALPHALEN);

    TRACEF(BUG) printf("stecker.c: "
                       "stecker_init(): "
                       "Before Parsing\n");
    /*
     * Parse through the stecker input and
     * set up the new alphabet.
     */
    

    if(swapMe)
    {
        word = strtok(swapMe, " ");
    }

    while(word && strlen(word) == 2)
    {
      /*
         * Only need to swap the necessary
         * characters.
         */
        s->alphabet[s->lookup(word[0])] = 
            alphabet[s->lookup(word[1])];
        s->alphabet[s->lookup(word[1])] =
            alphabet[s->lookup(word[0])];
        word = strtok(NULL, " ");
    }
    TRACEF(BUG) printf("stecker.c: "
                       "stecker_init(): "
                       "After Parsing and end\n");
    
    if(swapMe)
    {
        free(word);
    }
    TRACEF(BUG) printf("stecker.c: "
                       "stecker_init(): "
                       "After free(word)\n");
}

/*
 * stecker_encrypt()
 * --
 * Input:   Stecker*, const char
 * Output:  None
 * Return:  char
 * Notes:   This is pretty simple. It just maps one
 *          character to another. What a concept!
 */
char stecker_encrypt(Stecker* s, const char ch)
{
    TRACEF(BUG) printf("stecker.c: "
                       "stecker_encrypt(): "
                       "incomming = '%c'.\n", ch);
    TRACEF(BUG) printf("stecker.c: "
                       "stecker_encrypt(): "
                       "outgoing = '%c'.\n", 
                       s->alphabet[s->lookup(ch)]);
    return s->alphabet[s->lookup(ch)];
}
