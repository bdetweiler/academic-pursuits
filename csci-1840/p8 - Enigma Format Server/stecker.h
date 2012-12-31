/*
 * Enigma v 2.0
 * --
 * stecker.h
 * by Brian Detweiler
 */

#include"rotor.h"

/*
 * Maybe try an #ifndef ROTOR_H or something
 */
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ALPHALEN 26

typedef struct stecker
{
    /*
     * The alphabet of mappings.
     */
    char alphabet[ALPHALEN + 1]; //  = ALPHABET;

    char(*steckerSwap)(struct stecker*, const char);
    /*
     * This is from rotor.h
     */
    int (*lookup)     (const char);
}Stecker;


void stecker_init(   Stecker*, char*);
char stecker_encrypt(Stecker*, const char);
