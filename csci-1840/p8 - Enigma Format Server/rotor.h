/*
 * Enigma v 2.0
 * --
 * rotor.h
 * by Brian Detweiler
 */

/*
 * Uncomment to turn on Naval Rotors
 * #define _USE_NAVAL_ROTORS TRUE
 */

/* 
 * Standard alphabet
 */
#define ALPHABET       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

/*
 * This is the alphabet order for the rotors
 */
#define ROTOR_I        "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define ROTOR_II       "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define ROTOR_III      "BDFHJLCPRTXVZNYEIWGAKMUSQO"

#define ROTOR_IV       "ESOVPZJAYQUIRHXLNFTGKDCMWB"
#define ROTOR_V        "VZBRGITYUPSDNHLXAWMJQOFECK"

/*
 * Inverse of the Rotors
 */
#define ROTOR_I_REV    "UWYGADFPVZBECKMTHXSLRINQOJ"
#define ROTOR_II_REV   "AJPCZWRLFBDKOTYUQGENHXMIVS"
#define ROTOR_III_REV  "TAGBPCSDQEUFVNZHYIXJWLRKOM"

#define ROTOR_IV_REV   "HZWVARTNLGUXQCEJPMBSKDYOIF"
#define ROTOR_V_REV    "QCYLXWENFTZOSMVJUDKGIARPHB"

/* 
 * These are used for naval use and will not be used
 * in this version of the program. They are here for
 * scalability purposes.
 */
#ifdef _USE_NAVAL_ROTORS_
#define ROTOR_VI       "JPGVOUMFYQBENHZRDKASXLICTW"
#define ROTOR_VII      "NZJHGRCXMYSWBOUFAIVLPEKQDT"
#define ROTOR_VIII     "FKQHTLXOCBJSPDZRAMEWNIUYGV"
#define BETA           "LEYJVCNIXWPBQMDRTAKZGFUHOS"
#define GAMMA          "FSOKANUERHMBTIYCWLQPZXVGJD"

#define ROTOR_VI_REV   "SKXQLHCNWARVGMEBJPTYFDZUOI"
#define ROTOR_VII_REV  "QMGYVPEDRCWTIANUXFKZOSLJHB"
#define ROTOR_VIII_REV "QJINSAYDVKBFRUHMCPLEWZTGXO"
#define BETA_REV       "RLFOBVUXHDSANGYKMPZQWEJICT"
#define GAMMA_REV      "ELPZHAXJNYDRKFCTSIBMGWQVOU"
#endif


/*
 * If rotor I steps from X to U (Q to R), 
 * the next rotor is advanced
 */
#define NOTCH_I   "X"
/* 
 * If rotor steps from S to I (E to F), 
 * the next rotor is advanced
 */
#define NOTCH_II  "S"
/* 
 * If rotor steps from M to U (V to W), 
 * the next rotor is advanced
 */
#define NOTCH_III "M"
/* 
 * If rotor steps from Q to U (J to K), 
 * the next rotor is advanced
 */
#define NOTCH_IV  "Q"
/*
 * If rotor steps from K to V (Z to A), 
 * the next rotor is advanced
 */
#define NOTCH_V   "K"

/* 
 * These are the double notched rotors
 * These are used for naval use and will not be used
 * in this version of the program. They are here for
 * scalability purposes.
 */

#ifdef _USE_NAVAL_ROTORS_ 
/*
 * If rotor steps from W to J (Z to A), 
 * the next rotor is advanced
 * If rotor steps from N to H (M to N), 
 * the next rotor is advanced
 */
#define NOTCH_VI   "WN"
/* 
 * If rotor steps from T to N (A to Z), 
 * the next rotor is advanced
 * If rotor steps from B to O (M to N), 
 * the next rotor is advanced
 */
#define NOTCH_VII_1  "TB"
/* 
 * If rotor steps from V to F (A to Z), 
 * the next rotor is advanced
 * If rotor steps from P to D (M to N), 
 * the next rotor is advanced
 */
#define NOTCH_VIII_1 "VP"
#endif

/* 
 * Notes
 * -----
 * Leave room for adjusting the alphabet ring
 * relative to the core wiring.
 */

typedef struct rotor
{
    /*
     * Data members
     */

    /*
     * What physical rotor are we using? 1, 2, 3, 4, or 5?
     */
    int  rotorNum;

    /*
     * Where is the rotor in relation to the others?
     * 1 = left
     * 2 = middle
     * 3 = right
     */
    int  location;
    /* 
     * Just the alphabet
     */
    char alphabet[27]; 

    /* 
     * Array to hold the substitution alphabet
     */
    char alphaRing[27]; 

    /* 
     * Array to hold the REVERSE substitition alphabet
     */
    char alphaRingRev[27]; 
        
    /* 
     * Position to start in the array
     */
    int  offset;

    /* 
     * Position of the alphabet ring
     */
    int  ringSetting;

    /* 
     * Notch to control the stepping
     * Note: There is only one position on 
     * rotors I-V, but on the naval rotors, 
     * there are two, hence the extra place.
     */
    char knock[3];
    
    /*
     * Class Methods
     */
    char (*sub)(      struct rotor*, const char);
    char (*revSub)(   struct rotor*, const char);
    void (*step)(     struct rotor*);
    int  (*lookup)(   const  char);
    int  (*revLookup)(const  char*,  const char);
    void (*newOffset)(struct rotor*, const char);

}Rotor;

void rotor_init(  Rotor*, const int, const char, 
                  const char,  const int);
void rotorStep(   Rotor*);
/*
 * lookup
 */
int  findCharNum( const char);
/*
 * revLookup
 */
int  findCharPos( const char*, const char);
char rotorSub(    Rotor*, const char);
char rotorRevSub( Rotor*, const char);
void changeOffset(Rotor*, const char);
void error(const char*, const char*, const char*);
