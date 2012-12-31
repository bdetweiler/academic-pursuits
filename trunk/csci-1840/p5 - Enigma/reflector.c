#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include"reflector.h"

// Contains findCharNum()
#include"rotor.h"

#define BUG   2  // Change to zero to turn on debugging
#define DEBUG 1
#define TRACEF(x)		if ( DEBUG >= (x) )

/* rotor_init
 * --
 * Input:  a Rotor* and two ints
 * Output: "Incorrect reflector assignment" on error
 * Return: None
 * Notes:  Acts as a constructor for our Rotor struct.
 *         We set up the alphaRing, startPoint, stepControl,
 *         and set the function pointers equal to their 
 *         corresponding functions to make them class methods.
 */
void reflector_init(Reflector* r, char refType)
{
    TRACEF(BUG) printf("reflector.c: relector_init(): START\n");
    /* Set up whichever rotor we are using
     * and the notch to control the stepping
     */
    if(refType == 'B')
    {
        TRACEF(BUG) printf("reflector.c: relector_init(): refType == B\n");
        strncpy(r->alphaRing, REFLECTOR_B, sizeof(r->alphaRing));
    }
    else if(refType == 'C')
    {
        TRACEF(BUG) printf("reflector.c: relector_init(): refType == C\n");
        strncpy(r->alphaRing, REFLECTOR_C, sizeof(r->alphaRing));
    }
    else if(refType == 'X')
    {
        TRACEF(BUG) printf("reflector.c: relector_init(): refType == X\n");
        strncpy(r->alphaRing, REFLECTOR_X, sizeof(r->alphaRing));
    }
#if 0
    /* In case we decide to add the other two reflector types
     */
    else if(refType == 'D')
        strncpy(r->alphaRing, REFLECTOR_B_THIN, sizeof(r->alphaRing));
    else if(refType == 'E')
        strncpy(r->alphaRing, REFLECTOR_C_THIN, sizeof(r->alphaRing));
#endif
    else
    {
        fprintf(stderr, "reflector.c: reflector_init: Incorrect reflector assignment\n");
        // ToDo: It is also bitching about exit
        exit(EXIT_FAILURE);
    }



    TRACEF(BUG) printf("reflector.c: relector_init(): set class members\n");
    /* Reflector Type, in case we care.
     */
    r->reflectorType = refType;

    TRACEF(BUG) printf("reflector.c: relector_init(): set class methods\n");
    // CLASS METHODS
    r->sub           = reflectorSub;
    r->lookup        = findCharNum;
}

/* reflectorSub
 * -- 
 * Input:  struct Rotor*, const char
 * Output: "Char must be letter" on error
 * Return: Char for the substituted letter.
 */
char reflectorSub(Reflector* r, const char ch)
{
    TRACEF(BUG) printf("reflector.c: relectorSub(): START\n");
    // Get the number of the character we were sent
    int num;
        
    // If ch is not alpha A-Z
    if(isalpha(ch) == 0)
    {
        fprintf(stderr, "reflector.c: reflectorSub: Character must be a letter A-Z\n");
        exit(EXIT_FAILURE);
    }

    num = r->lookup(ch);

    // Return the appropriate substitution
    return r->alphaRing[num];
}

