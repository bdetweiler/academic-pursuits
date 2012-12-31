#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<assert.h>

#include"rotor.h"

#define BUG   2     // Make it 0 to debug
#define DEBUG 1 
#define TRACEF(x)		if ( DEBUG >= (x) )

/* rotor_init
 * --
 * Input:  a Rotor*, an int, a char 
 * Output: "Incorrect rotor assignment" on error
 * Return: None
 * Notes:  Acts as a constructor for our Rotor struct.
 *         We set up the alphaRing, startPoint, knock,
 *         and set the function pointers equal to their 
 *         corresponding functions to make them class methods.
 */
void rotor_init(Rotor* r, int rotorNum, char offset)
{
    /* 
     * Give us a copy of the alphabet. 
     */
    strncpy(r->alphabet,     ALPHABET,      sizeof(r->alphaRing));

    /* 
     * This is the "key", the starting point for the alphaRing.
     * We take the given char and look up its position on the
     * standard alphabet side. A = 0, B = 1, etc. 
     * It doesn't change.
     */
    r->ringSetting  = findCharNum(offset);

    /* 
     * Position to start in the array (offset from the start 
     * of the array 0 being the first element) We get this 
     * from the key. 
     * This will change with the stepping.
     */
    r->offset = r->ringSetting;
  
    /* 
     * We would probably like to know where this rotor is 
     * in relation to any others. Hence we store the given 
     * rotorNum.
     */ 
    r->rotorNum     = rotorNum;

    /* 
     * Set up whichever rotor we are using
     * and the notch to control the stepping
     */
    if(rotorNum == 1)
    {
        
        strncpy(r->alphaRing,    ROTOR_I,       sizeof(r->alphaRing));
        strncpy(r->alphaRingRev, ROTOR_I_REV,   sizeof(r->alphaRingRev));
        strncpy(r->knock,        NOTCH_I,       sizeof(r->knock));
    } 
    else if(rotorNum == 2)
    {

        strncpy(r->alphaRing,    ROTOR_II,      sizeof(r->alphaRing));
        strncpy(r->alphaRingRev, ROTOR_II_REV,  sizeof(r->alphaRingRev));
        strncpy(r->knock,        NOTCH_II,      sizeof(r->knock));
    } 
    else if(rotorNum == 3)
    {
        strncpy(r->alphaRing,    ROTOR_III,     sizeof(r->alphaRing));
        strncpy(r->alphaRingRev, ROTOR_III_REV, sizeof(r->alphaRingRev));
        strncpy(r->knock,        NOTCH_III,     sizeof(r->knock));
    } 
    else if(rotorNum == 4)
    {
        strncpy(r->alphaRing,    ROTOR_IV,      sizeof(r->alphaRing));
        strncpy(r->alphaRingRev, ROTOR_IV_REV,  sizeof(r->alphaRingRev));
        strncpy(r->knock,        NOTCH_IV,      sizeof(r->knock));
    }
    else if(rotorNum == 5)
    {
        strncpy(r->alphaRing,    ROTOR_V,       sizeof(r->alphaRing));
        strncpy(r->alphaRingRev, ROTOR_V_REV,   sizeof(r->alphaRingRev));
        strncpy(r->knock,        NOTCH_V,       sizeof(r->knock));
    }
    else
    {
        fprintf(stderr, "rotor.c: rotor_init: Incorrect rotor assignment\n");
        exit(EXIT_FAILURE);
    }

    // CLASS METHODS
    r->sub          = rotorSub;
    r->revSub       = rotorRevSub;
    r->step         = rotorStep;
    r->lookup       = findCharNum;
    r->revLookup    = findCharPos;
    r->newOffset    = changeOffset;
}

/*
 * changeOffset
 * --
 * Input:  const char
 * Output: none
 * Return: none
 * Notes:  Allows us to quickly and easily
 *         change the offset of the rotor.
 */
void changeOffset(Rotor* r, const char ch)
{
    r->ringSetting  = findCharNum(ch);
    r->offset       = r->ringSetting;
}

/* rotorSub
 * --
 * Input:  struct Rotor*, const char
 * Output: none
 * Return: A half-way encrypted character.
 * Notes:  This will encrypt the letter through
 *         the rotors going forward.  
 */
char rotorSub(Rotor* r, const char ch)
{
    int  tmp;
    /*
     * This will give us what it is coming
     * in as, offset included.
     */
    tmp  = (r->lookup(ch) + r->offset) % 26;

    /*
     * Grab the new position of the character
     * after it has zig-zagged back to the 
     * alphabet side using the character found
     * in the alphaRing[].
     */
    tmp  = r->lookup(r->alphaRing[tmp]);

    /* 
     * We want to return it as the standard 
     * alphabet character it would normally
     * be, so we can manipulate it with the 
     * next rotor's offset. Subtract this 
     * rotor's offset.
     */
    tmp -= r->offset;

    /* 
     * To play nice, we need to make sure
     * it is non-negative. We can add as many
     * 26s as we want, because modding them
     * will always give us the same result.
     */
    tmp += 26;

    /*
     * Speaking of modding...
     */
    tmp %= 26;

    /*
     * All we have now is the letter according
     * to the alphabet[]. To return an actual
     * character, let's add 'A' to it. This will
     * bump it up to an actual ASCII character.
     */
    return tmp + 'A';
}

/* rotorRevSub
 * -- 
 * Input:  struct Rotor*, const char
 * Output: "Char must be letter" on error
 * Return: The substituted character
 * Notes:  Same thing as rotorSub but we do it
 *         going backwards through the rotors.
 *         Update (October 27th, 12:19 am): 
 *         It finally fucking works after 2 
 *         Red Bulls, a strong coffee, and some
 *         Mountain Dew as a chaser. 
 */
char rotorRevSub(Rotor* r, const char ch)
{
    int  tmp;
    /* 
     * This takes the character that comes in 
     * and moves it to the correct offset so
     * it is where it should be coming in.
     * At this point, we only know which letter 
     * it is in the standard alphabet. It doesn't 
     * know where it is in the alphaRing[].
     */
    tmp  = (r->lookup(ch) + r->offset) % 26;
    /*
     * Here we get what letter it is in the 
     * standard alphabet.
     */
    tmp  = r->alphabet[tmp];

    /*
     * Here we do a reverse lookup. Basically,
     * we tell it to find what position in
     * alphaRing[] this letter is.
     */
    tmp  = r->revLookup(r->alphaRing, tmp); 

    /* 
     * Now, we get the number of characters
     * offset by subtracting the offset from
     * 26. Then we add the number of characters
     * offset to the current position and mod 
     * it by 26 to accomodate for wraparound. 
     * This gives us the real position in the
     * standard alphabet to be returned.
     */
    tmp  = ((26 - r->offset) + tmp) % 26;
    return tmp + 'A';
}

/* rotorStep
 * -- 
 * Input:  Struct Rotor*
 * Output: error if number greater than 25 or less than 0
 * Return: None
 * Notes:  Increments the initial position of a single rotor. 
 *         Note: To double step or anything else, it will have
 *         to be handled in the Spindle
 */
void rotorStep(Rotor* r)
{
    if(r->offset >= 0 && r->offset < 25)
    {
        ++(r->offset);
    }

    /* 
     * If the rotor hits the end, reset it to the beginning
     */
    else if(r->offset == 25)
    {
        r->offset = 0;
    }
    else
    {
        fprintf(stderr, "rotor.c: rotorStep: Illegal rotor movement.\n");
        exit(EXIT_FAILURE);
    }
}

/* findCharNum
 * --
 * Input:  a const char
 * Output: None
 * Return: An int between 0 and 25
 * Notes:  Takes an alphabet character and returns what position
 *         it is numerically (starting with 0). We can use this
 *         number to find the corresponding alpha character in 
 *         the rotor array.
 */
int findCharNum(const char ch)
{
    // If it is not an alpha character
    if(toupper(ch) < 'A' || toupper(ch) > 'Z')
    {
        exit(EXIT_FAILURE);
    }
    /* As long as there is a valid character, it will return an
     * int between 0 and 25.
     */
    return abs(('A' - toupper(ch)));
} // End findCharNum()

/* findCharPos
 * --
 * Input:  const char*, const char ch
 * Output: None
 * Return: An int between 0 and 25
 * Notes:  Finds the position of the character
 *         in the array using the character. 
 *         Basically, a reverse lookup using strchr.
 */
int findCharPos(const char* alphaRing, const char ch)
{
    // If it is not an alpha character
    if(toupper(ch) < 'A' || toupper(ch) > 'Z')
    {
        exit(EXIT_FAILURE);
    }

    char* tmp;
    int   pos;

    /*
     * This returns a string starting with 
     * the desired character.
     */
    tmp = strchr(alphaRing, ch);

    /* Since we know the string was originally
     * 26 characters long, if we subtract the new
     * string's length from 26, we will get the position
     * of our desired character.
     */
    pos = 26 - strlen(tmp);
    
    return pos;
} // End findCharPos()
// @end
