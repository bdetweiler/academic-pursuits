#include"spindle.h"

#define SIZE     5
#define KEYLEN   3
#define ROTORNUM 3

typedef struct enigma
{
    // The user's message
    // char message[BUFSIZ];
    // int  n;

    Rotor     left;
    Rotor     middle;
    Rotor     right;
    Reflector ref;
    Spindle   spindle;


    char* (*encrypt)(struct enigma*, const char*);
}Enigma;

// void rotor_init(  Rotor*, int, char);
void  engima_init(   Enigma*, const int*, const char*, const char);
char* enigma_encrypt(Enigma*, const char*);

