#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

#include"enigma.h"

void enigma_init(Enigma* e, const int* rotorOrder, const char* key, const char reflectorType)
{
printf("enigma.c: enigma_init(): START\n");
    Rotor     left;
    Rotor     middle;
    Rotor     right;
    Reflector ref;
    Spindle   spindle;

    rotor_init(&left,   rotorOrder[0], key[0]);
    rotor_init(&middle, rotorOrder[1], key[1]);
    rotor_init(&right,  rotorOrder[2], key[2]);
    
    reflector_init(&ref, reflectorType);

    spindle_init(&spindle);
    
    spindle.addReflector(&spindle, &ref);

    spindle.addRotor(&spindle, &left);
    spindle.addRotor(&spindle, &middle);
    spindle.addRotor(&spindle, &right);

    e->encrypt = enigma_encrypt;
}
    
char* enigma_encrypt(Enigma* e, const char* message)
{
printf("enigma.c: enigma_encrypt(): START\n");
printf("enigma.c: enigma_encrypt(): message = %s\n", message);
    static char* encryptedMsg;
printf("enigma.c: enigma_encrypt(): declared static char* encryptedMsg\n");
    encryptedMsg = malloc(strlen(message) + 1);
printf("enigma.c: enigma_encrypt(): malloc'd encryptedMsg\n");
    assert(encryptedMsg);
printf("enigma.c: enigma_encrypt(): asserted encryptedMsg\n");
printf("enigma.c: enigma_encrypt(): I am about to piss it off and segfault\n");
printf("enigma.c: enigma_encrypt(): e->spindle.encrypt(): %s\n", e->spindle.encrypt(&(e->spindle), message));
                

    strncpy(encryptedMsg, 
                e->spindle.encrypt(&(e->spindle), message), 
                    strlen(message));

    return encryptedMsg;
}
