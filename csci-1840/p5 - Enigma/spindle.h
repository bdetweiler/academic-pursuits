#include"rotor.h"
#include"reflector.h"

#define decrypt encrypt

typedef struct spindle
{

    // Key for encryption
    char key[4];

    Rotor right;
    Rotor middle;
    Rotor left;

    Reflector ref;


    char* (*encrypt)(     struct spindle*, const char*);
    void  (*addRotor)(    struct spindle*, struct rotor*);
    void  (*addReflector)(struct spindle*, struct reflector*);
}Spindle;

void  spindle_init(Spindle*);
char* spindle_encrypt(Spindle*, const char*);
void  spindle_addRotor(Spindle*, Rotor*);
void  spindle_addReflector(Spindle*, Reflector*);

// Could be a static function
char  char_encrypt(Spindle*, char);

