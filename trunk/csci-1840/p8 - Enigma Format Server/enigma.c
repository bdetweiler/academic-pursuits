/*
 * Enigma v 2.0
 * --
 * main.c
 * by Brian Detweiler
 */

#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/wait.h>

// #include"enigma.h"
#include"spindle.h"
#include"socket.h"

#define SPNDLSIZE 3 
#define KEYSIZE   3
#define LEFT      1 
#define MIDDLE    2 
#define RIGHT     3

// debugging shit
#define BUG       2     // Something greater than 1 to debug
#define DEBUG     1
#define TRACEF(x)		if ( DEBUG >= (x) )

#define SPACE     32
#define NEWLINE   10
#define TAB       9 

int   rtoi( const char*);
char* itor( const int);
void  parse(char*, char*, char*, char*, char*, char*, char*);
char* trim(char*);
    

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
    int   rotorOrder[  SPNDLSIZE];   // = {1, 2, 3};
    char  rings[       SPNDLSIZE + 1];
    char  initRotorPos[KEYSIZE   + 1]; // = "AAA";
    char  key[         KEYSIZE   + 1]; // = "AAA";
    char  steckers[    ALPHALEN  + 13 + 1];

    /*
     * User input SETTINGS
     */
    char  settings[    BUFSIZ];

    /*
     * The user's message
     */
    char  message[     BUFSIZ];      // = "TESTING";
    char  encryptedMsg[BUFSIZ];
   
    /*
     * fork()/exec() stuff
     */ 
    int   status;
    // TODO: Get a dynamic way to put a port number in there.
    char* cmd[] = { "server", "-p", "2600", NULL };
    char* env[] = { NULL };
    pid_t pid;
    // encryptedMsg = malloc(strlen(message) + 1);
    // assert(encryptedMsg);

    /* 
     * <ENIGMA>
     */
    Stecker   stecker;
    Rotor     left;
    Rotor     middle;
    Rotor     right;
    Reflector ref;
    Spindle   spindle;
    /* 
     * </ENIGMA>
     */


    if(argc == 2)
        error("enigma", "main", "Too few arguments.");
    if(argc > 3)
        error("enigma", "main", "Too many arguments.");
    if(argc == 3)
        if(strcasecmp(argv[1], "-f") != 0)
            error("enigma", "main", "Usage: enigma -f <port>");

    /*
     * <SETTINGS> 
     */
    printf("Enter Enigma's configuration, key, and message:\n"); 
    printf("Example:\n"
           "B | I II III | ABC | AB CD EF GH IJ KL MN OP QR ST UV WX YZ\n"
           "AAA AAA\n"
           "THISX ISXAT EST\n");
   
    /*
     * This will give us the settings to parse
     */
    fgets(settings, BUFSIZ, stdin);

    /*
     * Parse the settings
     */
    parse(settings, &reflectorType, rotor1, rotor2, rotor3, rings, steckers);

    /*
     * Initial window position
     */
    scanf("%3s", initRotorPos);
    
    /*
     * Key
     */
    scanf("%3s", key);

    /*
     * Message
     */ 
    while(fgets(message, BUFSIZ, stdin) != NULL)
    {;;;}
    
    /* 
     * Rotor order
     */
    rotorOrder[0] = rtoi(rotor1);
    rotorOrder[1] = rtoi(rotor2);
    rotorOrder[2] = rtoi(rotor3);
    rotor_init(         &left,     rotorOrder[0], initRotorPos[0], rings[0], LEFT);
    rotor_init(         &middle,   rotorOrder[1], initRotorPos[1], rings[1], MIDDLE);
    rotor_init(         &right,    rotorOrder[2], initRotorPos[2], rings[2], RIGHT);
    reflector_init(      &ref,     reflectorType);

    spindle_init(        &spindle);


    spindle.addReflector(&spindle, &ref);

    spindle.addRotor(    &spindle, &left);
    spindle.addRotor(    &spindle, &middle);
    spindle.addRotor(    &spindle, &right);

    stecker_init(        &stecker, steckers);

    spindle.stecker = stecker;
    // spindle.addStecker(  &spindle, &stecker);
    
    strncpy(key, 
                spindle.encrypt(&spindle, key), 
                    KEYSIZE + 1);
    /*
     * strncpy does't null-terminate
     */
    key[3] = '\0';
    
    /*
     * Now key is the newly encrypted key. Reset
     * the rotors to that key. Change the offsets 
     * of the rotors based on the key.
     */
    spindle.left.newOffset(  &(spindle.left),   key[0]);
    spindle.middle.newOffset(&(spindle.middle), key[1]);
    spindle.right.newOffset( &(spindle.right),  key[2]);
    // </ENIGMA>
   

    /*
     * TODO: May need to manually add the '\0' at the end
     */
    strncpy(encryptedMsg, 
                spindle.encrypt(&spindle, message), 
                    strlen(message) + 1);
    /*
     * Print out all the stats and the 
     * encrypted message.
     */
    printf("reflector is '%c'\n", spindle.ref.reflectorType);
    printf("rotor is '%s' ring setting is '%c'\n", itor(spindle.left.rotorNum), spindle.left.ringSetting);
    printf("rotor is '%s' ring setting is '%c'\n", itor(spindle.middle.rotorNum), spindle.middle.ringSetting);
    printf("rotor is '%s' ring setting is '%c'\n", itor(spindle.right.rotorNum), spindle.right.ringSetting);
    printf("plugboard is '%s'\n", spindle.stecker.alphabet);
    printf("initial window position is '%c%c%c'\n", initRotorPos[0], 
                initRotorPos[1], initRotorPos[2]);
    printf("encrypted message key is '%c%c%c'\n", initRotorPos[0], 
                initRotorPos[1], initRotorPos[2]);
    printf("decrypted message key is '%c%c%c'\n", key[0], 
                key[1], key[2]);

 
    /*
     * TODO: Message needs to go through server to be formatted.
     */
    if(argv[2])
    {
        pid = fork();

        if(pid == -1)
        {
            printf("Fork failed\n");
            exit(1);
        }
        if(pid == 0)
        {
            sleep(1);
            execve("./eformatsvr/run_server", cmd, env);
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }


    printf("Encrypted Message: %s\n", encryptedMsg);

    return 0;
}

void parse(char* settings, char* reflectorType, 
           char* rotor1,   char* rotor2, 
           char* rotor3,   char* rings, 
           char* steckers)
{
    char*  tok;
    char*  tok2;
    int    i;
    int    j;
    int    k;
    int    counter;

    // "B | I II III | ABC | AB CD EF GH IJ KL MN OP QR ST UV WX YZ\n"

    settings = trim(settings);
    tok      = malloc(strlen(settings) * sizeof(char));
    tok2     = malloc(strlen(settings) * sizeof(char));

    tok      = strtok(settings, "|");
    for(counter = 0; tok && counter <= 3; ++counter)
    {
        /* 
         * Remove leading and trailing whitespace
         */
        tok = trim(tok);

        switch(counter)
        {
/*********************************************************
 *                      Reflector                        *
 *********************************************************/
            case 0:
                /*
                 * First off, if it is more than 1 character, exit.
                 */
                if(strlen(tok) > 1)
                    error("main", "parse", "Reflector must be one letter");

                if(     strchr(tok,  'B'))
                    *reflectorType = 'B';
                else if(strchr(tok,  'C'))
                    *reflectorType = 'C';
                else if(strchr(tok,  'X'))
                    *reflectorType = 'X';
                    /*
                     * They entered an incorrect rotor type.
                     */
                else
                    error("main", "parse", "Wrong reflector type. Candidates are: B, C, X");
                break;
            
/*********************************************************
 *                  Rotor Assignments                    *
 *********************************************************/
            case 1: 
                /*
                 * Go through the 3 rotors
                 */
                k = 0;

                for(i = 0; i <= 2; ++i)
                {
                    for(j = 0; 
                        tok[k] != SPACE   &&
                        tok[k] != NEWLINE && 
                        tok[k] != TAB     &&
                        tok[k] != '\0';    
                        ++j && ++k)
                    {
                        tok2[j] = toupper(tok[k]);
                    }
                    ++k;

                    if(     i == 0)
                    {
                        strncpy(rotor1, tok2, SPNDLSIZE);
                        rotor1[strlen(tok2)] = '\0';
                    }
                    else if(i == 1)
                    {
                        strncpy(rotor2, tok2, SPNDLSIZE);
                        rotor2[strlen(tok2)] = '\0';
                    }
                    else if(i == 2)
                    {
                        strncpy(rotor3, tok2, SPNDLSIZE);
                        rotor3[strlen(tok2)] = '\0';
                    }
                }
                break;

/*********************************************************
 *                  Ring Settings                        *
 *********************************************************/
            case 2: 
                if(strlen(tok) != 3)
                    error("main", "parse", "Incorrect ring settings. I need 3 characters.");
                
                strncpy(rings, tok, SPNDLSIZE + 1);
                rings[SPNDLSIZE + 1] = '\0';
                break;

/*********************************************************
 *                  Steckers                             *
 *********************************************************/
            case 3:
                if(strlen(tok) > ALPHALEN + 13 + 1)
                    error("main", "parse", "Incorrect stecker settings.");

                strncpy(steckers, tok, ALPHALEN + 13 + 1);
                steckers[ALPHALEN + 13 + 1] = '\0';
                break;
/*********************************************************
 *                  Error                                *
 *********************************************************/
            default:
                error("main", "parse", "Too many arguments.");
                break;
        }

        /*
         * Grab the next token
         */
        tok = strtok(NULL, "|");
    } // End For Loop

    /*
     * Free the tokens
     */
    free(tok);
    free(tok2);
}

/*
 * rtoi (Roman To Integer)
 * --
 * Input:   A char*
 * Output:  none
 * Return:  The integer equivalent of the roman numeral
 * Notes:   Send this function a string of roman numerals
 *          and it will send back the integer equivalent.
 *          Right now, it is not a full-fledged rtoi().
 *          It just gives us what we want.
 */
int rtoi(const char* roman)
{
    int rval;

    if(strcasecmp(     roman, "I")   == 0)
        rval = 1;
    else if(strcasecmp(roman, "II")  == 0)
        rval = 2;
    else if(strcasecmp(roman, "III") == 0)
        rval = 3;
    else if(strcasecmp(roman, "IV")  == 0)
        rval = 4;
    else if(strcasecmp(roman, "V")   == 0)
        rval = 5;
    else
        error("main", "rtoi", "Incorrect roman numeral type.");

    return rval;
}
 
/*
 * itor (Integer To Roman)
 * --
 * Input:   A char*
 * Output:  none
 * Return:  The Roman numeral equivalent of the integer
 * Notes:   Send this function an integer, and you will
 *          get a Roman numeral back. Only good for 1-5.
 *
 */
char* itor(const int rotorNum)
{
    char* rval;

    if(     rotorNum == 1)
        rval = "I"; 
    else if(rotorNum == 2)
        rval = "II"; 
    else if(rotorNum == 3)
        rval = "III"; 
    else if(rotorNum == 4)
        rval = "IV"; 
    else if(rotorNum == 5)
        rval = "IV"; 
    else
        error("main", "itor", "No such rotor.");

    return rval;
}

/*
 * trim()
 * --
 * Input:   char*
 * Output:  None
 * Return:  char*
 * Notes:   Since there is no trim() function in any of the
 *          c libraries, I decided to write one. This is not
 *          the best trim function ever, but it works. There
 *          is room for improvement, but that is for later. 
 *
 *          Example: "____blah blah blah______" ("___" == spaces)
 *          Return : "blah blah blah"
 *
 *          This works for spaces and tabs. 
 */
char* trim(char* trimMe)
{
    int   i    = 0;
    int   j    = 0;
    int   flag = 1;
    char* tmp;
    tmp = malloc(strlen(trimMe) * sizeof(char));

    /*
     * Copy everything into tmp
     */
    strncpy(tmp, trimMe, strlen(trimMe));
    tmp[strlen(trimMe)] = '\0';
    
    /*
     * Zero out trimMe
     */
    memset(trimMe, 0, strlen(trimMe));

    /*
     * Front of array
     * Set the starting point
     */
    for(i = 0; tmp[i] != '\0'; ++i)
    {
        if(tmp[i] != TAB && tmp[i] != SPACE && tmp[i] != SPACE)
            flag = 0;

        if(flag == 1)
            ++j;
    }
   
    /*
     * reset flag
     */ 
    flag = 1;

    /*
     * Start copying from the starting point.
     * Now we are rid of the leading spaces.
     */
    for(i = 0; tmp[j] != '\0'; ++i && ++j)
        trimMe[i] = tmp[j];
    
    /*
     * Once we hit something other than a
     * space or tab or new line, place the null right after it.
     * Now we are rid of the trailing spaces.
     */
    for(i = strlen(trimMe) - 1; i >= 0 && flag != 0; --i)
    {
        if(trimMe[i] != TAB && trimMe[i] != SPACE && trimMe[i] != NEWLINE)
        {
            trimMe[i + 1] = '\0';
            flag = 0;
        }
    }
    free(tmp);
    return trimMe;
}

