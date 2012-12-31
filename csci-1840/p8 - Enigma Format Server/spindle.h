/*
 * Enigma v 2.0
 * --
 * spindle.h
 * by Brian Detweiler
 */

#include"stecker.h"
// #include"rotor.h"
#include"reflector.h"

#define decrypt encrypt

typedef struct spindle
{

    // Key for encryption
    char key[4];

    Stecker   stecker;

    Rotor     right;
    Rotor     middle;
    Rotor     left;

    Reflector ref;


    char* (*encrypt)(     struct spindle*, const char*);
    void  (*addRotor)(    struct spindle*, struct rotor*);
    void  (*addReflector)(struct spindle*, 
                          struct reflector*);
    void  (*addStecker)(  struct spindle*, struct stecker*);
}Spindle;

void  spindle_init(        Spindle*);
char* spindle_encrypt(     Spindle*, const char*);
void  spindle_addRotor(    Spindle*, Rotor*);
void  spindle_addReflector(Spindle*, Reflector*);
void  spindle_addStecker(  Spindle*, Stecker*);

// Could be a static function
char  char_encrypt(        Spindle*, char);

