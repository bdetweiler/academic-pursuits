/*
 * Enigma v 2.0
 * --
 * spindle.c
 * by Brian Detweiler
 */


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<ctype.h>
#include<string.h>

#include"spindle.h"

#define BUG   2   // Change to 0 to turn on debugging
#define DEBUG 1
#define TRACEF(x)		if ( DEBUG >= (x) )

void spindle_init(Spindle* s)
{
    TRACEF(BUG) printf("spindle.c:"
                       " spindle_init():"
                       " START\n");
    /* 
     * Class Methods
     */
    s->encrypt      = spindle_encrypt;
    s->addRotor     = spindle_addRotor;
    s->addReflector = spindle_addReflector;
}

char* spindle_encrypt(Spindle* s, const char* message)
{
    int doubleStep = 0; 
    int i; 
    // static char* tmp;
    static char* rval;
    /*
     * ToDo: Free()
     */
    rval = malloc(strlen(message) + 1); 

    TRACEF(BUG) printf("spindle.c: spindle_encrypt():"
                       " START\n");
    // rval = malloc(strlen(message) + 1);
    // assert(rval);
    TRACEF(BUG) printf("spindle.c: spindle_encrypt():"
                       " malloc rval\n");
   
    TRACEF(BUG) printf("spindle.c: spindle_encrypt():"
                       " entering for loop\n");
    for(i = 0; i < strlen(message) + 1; ++i)
    {
        TRACEF(BUG) printf("spindle.c: spindle_encrypt():"
                           " in for loop\n");
    
        /* 
         * *** DO STEPPING HERE ***
         */

        TRACEF(BUG) printf("spindle.c: spindle_encrypt():"
                           " step right rotor\n");
        
        /*
         * Right rotor steps each time independently 
         * of everything else.
         */
        if('A' <= toupper(message[i]) && 
           'Z' >= toupper(message[i]))
        {
            s->right.step(&(s->right));
        }

        /*
         * This takes care of the double stepping case. 
         * ToDo: Test!!! What if it starts on this rotor?
         */
        if(doubleStep == 1)
        {
            TRACEF(BUG) printf("spindle.c:"
                               " spindle_encrypt():"
                               " doublestep\n");
            s->middle.step(&(s->middle));
            s->left.step(&(s->left));
            doubleStep = 0;
        }

        /* 
         * If the right rotor has passed it's notch position
         * Note: In the Enigma machine, the right rotor 
         * falls into the notch position on one step then 
         * on the next step moves the rotor.
         * We are not messing with that shit. 
         * We test to see if the previous was the notch 
         * position, which would mean that we just passed 
         * it and we say, "Ooh, look! I should step the 
         * middle rotor now!"
         */
        else if(strchr(s->right.knock, 
                    s->right.alphaRing[
                    ((26 + s->right.offset) - 1) % 26]) 
                    != NULL)
        {
            TRACEF(BUG) printf("spindle.c:"
                               " spindle_encrypt():"
                               " step middle rotor\n");
            /*
             * Step the middle rotor
             */
            s->middle.step(&(s->middle));
            if(strchr(NOTCH_II, 
                        s->middle.alphaRing[
                            s->middle.offset]) != NULL)
            {
                TRACEF(BUG) printf("spindle.c:"
                                   " spindle_encrypt():"
                                   " turn on doublestep\n");
                doubleStep = 1;
            }
        }
        
        /* 
         * Finally, encrypt the character and store it in
         * the rval array to be returned at the end of the 
         * function.
         */
        rval[i] = char_encrypt(s, message[i]);
    }
    rval[i] = '\0';
    /* 
     * Return the encrypted char 
     */
    return rval;
} /* End spindle_encrypt() */


char char_encrypt(Spindle* s, char ch)
{
    /*
     * In here, check to see if it is a space, or whatever
     */
    char rval;

    TRACEF(BUG) printf("spindle.c: char_encrypt(): START\n");
    /* 
     * Check to make sure it is an alpha character A-Z
     */
    if('A' <= toupper(ch) && 
       'Z' >= toupper(ch))
    {
        TRACEF(BUG) printf("spindle.c:"
                           " char_encrypt():"
                           " isalpha(%c)\n", ch);
        /*
         * Use rval from here on out
         */
        rval = ch;

        /*
         * STECKER
         */        
        rval = s->stecker.steckerSwap(&(s->stecker), rval);

        /*
         * Forward through the rotors:
         *           RIGHT
         *     MIDDLE
         * LEFT
         */
        TRACEF(BUG) printf("spindle.c:"
                           " char_encrypt():" 
                           " rotor.sub\n");

        rval = s->left.sub(&(s->left), 
                    s->middle.sub(&(s->middle),
                        s->right.sub(&(s->right), rval)));

        /*
         * Hit the REFLECTOR
         */
        TRACEF(BUG) printf("spindle.c:"
                           " char_encrypt():"
                           " ref.sub\n");
        rval = s->ref.sub(&(s->ref), rval);

        /* 
         * Reverse back through the rotors
         * RIGHT
         *      MIDDLE
         *            LEFT
         */
        TRACEF(BUG) printf("spindle.c:" 
                           " char_encrypt():"
                           " ref.revSub\n");
        rval = s->right.revSub(&(s->right),
                    s->middle.revSub(&(s->middle), 
                        s->left.revSub(&(s->left), rval)));
        /*
         * STECKER
         */        
        rval = s->stecker.steckerSwap(&(s->stecker), rval);
    }
    else if(ch >= 0 && ch <= 32)
    {
        /* 
         * If it is between 1 (SOH) and 32 (SPACE)
         * just return it as a space.
         */
        rval = 32; 
    }
#if 1 
    /*
     * We would use this to fail if an invalid character 
     * came through.
     */
    else
        error("spindle", "char_encrypt", 
              "Not a valid character. "
              "Only A-Z and Spaces are valid.");
#endif 
    return rval;
} /* End char_encrypt() */



/* spindle_addRotor
 * --
 * Input:  A Spindle* and a Rotor*
 * Output: None
 * Return: None
 * Notes:  Add a rotor to the spindle. The rotor and spindle
 *         will have already been initialized. 
 */
void spindle_addRotor(Spindle* s, Rotor* r)
{
    TRACEF(BUG) printf("spindle.c:"
                       " spindle_addRotor():" 
                       " START\n");
    if(r->location == 1)
    {
        TRACEF(BUG) printf("spindle.c:"
                           " spindle_addRotor():" 
                           " rotorNum == 1\n");
        /*
         * Set this to LEFT rotor
         */
        s->left   = *r;
    }
    else if(r->location == 2)
    {
        TRACEF(BUG) printf("spindle.c:"
                           " spindle_addRotor():"
                           " rotorNum == 2\n");
        // Set this to MIDDLE rotor
        s->middle = *r;
    }
    else if(r->location == 3)
    {
        TRACEF(BUG) printf("spindle.c:"
                           " spindle_addRotor():"
                           " rotorNum == 3\n");
        // Set this to RIGHT rotor
        s->right  = *r;
    }

}

/* spindle_addReflector
 * --
 * Input:  A Spindle* and a Reflector*
 * Output: None
 * Return: None
 * Notes:  Add a reflector to the spindle. The reflector 
 *         and spindle will have already been initialized. 
 */
void spindle_addReflector(Spindle* s, Reflector* r)
{
    TRACEF(BUG) printf("spindle.c:"
                       " spindle_addReflector():"
                       " START\n");
    s->ref = *r;
}

/* spindle_addStecker
 * --
 * Input:  A Spindle* and a Stecker*
 * Output: None
 * Return: None
 * Notes:  Add a stecker to the spindle. The stecker 
 *         and spindle will have already been initialized. 
 */
void spindle_addStecker(Spindle* s, Stecker* st)
{
    TRACEF(BUG) printf("stecker.c:"
                       " spindle_addStecker():"
                       " START\n");
    s->stecker = *st;
}
