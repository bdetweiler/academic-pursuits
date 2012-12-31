#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<assert.h>

// #include"enigma.h"
#include"spindle.h"

#define SPNDLSIZE 3 
#define KEYSIZE   3

// debugging shit
#define BUG   0     // Something greater than 1 to debug
#define DEBUG 1
#define TRACEF(x)		if ( DEBUG >= (x) )

int   rtoi(const char*);
char* itor(const int);
/*
 * ToDo:    
 *          * Work on taking the message input.
 */

/*
 * We take the initial rotor position and set that.
 * Then we take the key given and encrypt it with the
 * initial rotor position. Then we reset the positions
 * to the encrypted key. Then we encrypt the message
 * with the new key.
 */
int main(int argc, char** argv)
{
    // char  n;
    // int   i;
    char  rotor1[SPNDLSIZE + 1];
    char  rotor2[SPNDLSIZE + 1];
    char  rotor3[SPNDLSIZE + 1];
    // char  input[ SPNDLSIZE + 1];
    // char  buf[   BUFSIZ]; //  = {1, 2, 3};

    // The user's settings
    char  reflectorType;             // = 'B';
    int   rotorOrder[  SPNDLSIZE];     //  = {1, 2, 3};
    char  initRotorPos[KEYSIZE + 1]; // = "AAA";
    char  key[         KEYSIZE + 1];          // = "AAA";

    // The user's message
    char  message[     BUFSIZ]; // = "TESTING";
    char  encryptedMsg[BUFSIZ];
    
    // encryptedMsg = malloc(strlen(message) + 1);
    // assert(encryptedMsg);

    /* 
     * <ENIGMA>
     */
    Rotor     left;
    Rotor     middle;
    Rotor     right;
    Reflector ref;
    Spindle   spindle;
    /* 
     * </ENIGMA>
     */



    /*
     * <SETTINGS> 
     */
    printf("Enter Enigma's configuration, key, and message:\n"); 
    printf("Example:\n"
           "B I II III\n"
           "AAA AAA\n"
           "THISX ISXAT EST\n");

    /*
     * Reflector
     */
    // scanf("%c", &reflectorType);
    reflectorType = fgetc(stdin);

    /* 
     * Rotors
     */
    scanf("%3s", rotor1);
    scanf("%3s", rotor2);
    scanf("%3s", rotor3);
    
    /*
     * Initial window position
     */
    scanf("%3s", initRotorPos);
    
    /*
     * Initial window position
     */
    scanf("%3s", key);
    /*
     * Message
     */ 
    /*
     * while(read(0, buf, BUFSIZ) != EOF)
     * {
     *      strncat(
     */

    while(fgets(message, BUFSIZ, stdin) != NULL)
    {;;;}
    
    /*
    for(i = 0; n != EOF; ++i)
    {
        n = getc(stdin); 
printf("message = %s\n", message);
        message[i] = n;
    }
    */ 
printf("1\n");
    /* 
     * Rotor order
     */
    rotorOrder[0] = rtoi(rotor1);
    rotorOrder[1] = rtoi(rotor2);
    rotorOrder[2] = rtoi(rotor3);
printf("2\n");
    
    /*
     * <ENIGMA>
     */
    rotor_init(&left,   rotorOrder[0], initRotorPos[0]);
    rotor_init(&middle, rotorOrder[1], initRotorPos[1]);
    rotor_init(&right,  rotorOrder[2], initRotorPos[2]);

printf("3\n");

    reflector_init(&ref, reflectorType);

printf("4\n");
    spindle_init(&spindle);

printf("5\n");
    spindle.addReflector(&spindle, &ref);

printf("6\n");
    spindle.addRotor(&spindle, &left);
    spindle.addRotor(&spindle, &middle);
    spindle.addRotor(&spindle, &right);
    
printf("7\n");
    strncpy(key, 
                spindle.encrypt(&spindle, key), 
                    KEYSIZE + 1);
    /*
     * strncpy does't null-terminate
     */
    key[3] = '\0';
    
printf("8\n");
    /*
     * Now key is the newly encrypted key. Reset
     * the rotors to that key. Change the offsets 
     * of the rotors based on the keys.
     */
    spindle.left.newOffset(  &(spindle.left),   key[0]);
    spindle.middle.newOffset(&(spindle.middle), key[1]);
    spindle.right.newOffset( &(spindle.right),  key[2]);
    // </ENIGMA>
    
printf("9\n");
    strncpy(encryptedMsg, 
                spindle.encrypt(&spindle, message), 
                    strlen(message) + 1);
printf("10\n");
    /*
     * Print out all the stats and the 
     * encrypted message.
     */
    printf("reflector is '%c'\n", spindle.ref.reflectorType);
    printf("rotor is '%s'\n", itor(spindle.left.rotorNum));
    printf("rotor is '%s'\n", itor(spindle.middle.rotorNum));
    printf("rotor is '%s'\n", itor(spindle.right.rotorNum));
    printf("initial window position is '%c%c%c'\n", initRotorPos[0], 
                initRotorPos[1], initRotorPos[2]);
    printf("encrypted message key is '%c%c%c'\n", initRotorPos[0], 
                initRotorPos[1], initRotorPos[2]);
    printf("decrypted message key is '%c%c%c'\n", key[0], 
                key[1], key[2]);
    printf("Encrypted Message: %s\n", encryptedMsg);
    return 0;
#if 0
    Enigma e;

    enigma_init(&e, &rotorOrder, &key, reflectorType);

    while((n = read(0, buf, BUFSIZ)) > 0)
        strncat(message, buf, BUFSIZ);

    encryptedMsg = (char*)malloc(strlen(message));

    // ENCRYPT
    encryptedMsg = e.encrypt(&e, message);
    // write(1, message, n);
    // {;;;} 

    // message = realloc(message, strlen(message) + SIZE);

    // Make sure arr was allocated ok
    // assert(message);


    // printf("%s\n", spindle.encrypt(&spindle, message));
#endif
}

/*
 * rtoi (Roman To Integer)
 * --
 * Input:  A char*
 * Output: none
 * Return: The integer equivalent of the roman numeral
 * Notes:  Send this function a string of roman numerals
 *         and it will send back the integer equivalent.
 *         Right now, it is not a full-fledged rtoi().
 *         It just gives us what we want.
 */
int rtoi(const char* roman)
{
    int rval;

    if(strcmp(roman, "I") == 0)
    {
        rval = 1;
    }
    else if(strcmp(roman, "II") == 0)
    {
        rval = 2;
    }
    else if(strcmp(roman, "III") == 0)
    {
        rval = 3;
    }
    else if(strcmp(roman, "IV") == 0)
    {
        rval = 4;
    }
    else if(strcmp(roman, "V") == 0)
    {
        rval = 5;
    }
    else
    {
        fprintf(stderr, "main.c: rtoi(): Incorrect roman numeral type.\n");
        exit(EXIT_FAILURE);
    }

    return rval;
}
    
char* itor(const int rotorNum)
{
    char* rval;
    if(rotorNum == 1)
    {
        rval = "I"; 
    }
    if(rotorNum == 2)
    {
        rval = "II"; 
    }
    if(rotorNum == 3)
    {
        rval = "III"; 
    }
    if(rotorNum == 4)
    {
        rval = "IV"; 
    }
    if(rotorNum == 5)
    {
        rval = "IV"; 
    }
    return rval;
}
