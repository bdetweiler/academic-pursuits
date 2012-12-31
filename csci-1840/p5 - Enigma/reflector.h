// Standard alphabet
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

// These are the reflectors. They don't move.
#define REFLECTOR_B "YRUHQSLDPXNGOKMIEBFZCWVJAT"
#define REFLECTOR_C "FVPJIAOYEDRZXWGCTKUQSBNMHL"
// This is the reflector from the paper machine
#define REFLECTOR_X "ABCDEFGDIJKGMKMIEBFTCVVJAT"
/* These are used for naval use and will not be used
 * in this version of the program. They are here for
 * scalability purposes.
 * #define REFLECTOR_B_THIN "ENKQAUYWJICOPBLMDXZVFTHRGS"
 * #define REFLECTOR_C_THIN "RDOBJNTKVEHMLFCWZAXGYIPSUQ"
 */


typedef struct reflector
{
    // Data members

    /* Is it a B, C, B Thin, or C Thin? (The thins can
     * be represented with D and E
     */
    char reflectorType;

    // Array to hold the substitution alphabet +1 for \0
    char alphaRing[27]; 
        
    // Class Methods
    char (*sub)(   struct reflector*, const char);
    int  (*lookup)(const char);

}Reflector;

// Initialize the rotor
void reflector_init( Reflector*, const char);
char reflectorSub(   Reflector*, const char);

