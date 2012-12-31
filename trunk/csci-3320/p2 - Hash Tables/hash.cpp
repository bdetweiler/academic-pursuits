/****************************************************************************
 * File:    hash.cpp                                                        *
 * Author:  Brian Detweiler                                                 *
 * Use:     A hash lookup table for lists of dictionary words using         *
 *          a Soundex code for the key.                                     *
 ***************************************************************************/

#include"hash.h"


/* Default Constructor
 * ---
 * Input:   none
 * Output:  none
 * Return:  none
 * Big-O:   O(n) for n = TABLE_SIZE
 * Notes:   Initializes a new hash table by instantiating a List in
 *          each of TABLE_SIZE slots.
 */
Hash::Hash(void)
{
    // Have to set up our table by creating the lists first
    for(u_int i = 0; i < TABLE_SIZE; ++i)
        table.push_back(new List());
}

/* getTable()
 * ---
 * Input:   none
 * Output:  none
 * Return:  vector<List*>
 * Big-O:   N/A
 * Notes:   Gives direct access to the table. Mostly for testing purposes.
 */
vector<List*> Hash::getTable(void)
{
    return table;
}


/* insert()
 * ---
 * Input:   char*, char*   
 * Output:  none
 * Return:  none
 * Big-O:   O(n) - Potentially could have to look in every slot for an opening. 
 *          Amortized O(1) if the hash function is low on clustering.
 * Notes:   Inserts a key-value pair into the hash table
 * Example: key = "A0231"
 *          value = "Asshole"
 */
void Hash::insert(char* key, char* value)
{

    // If the input values are not empty, 
    if(*value && *key)
    {
        (*lookup(key)).setSoundex(key);

        (*lookup(key)).insert(value);
    }
    else
    {
        cerr << "Hash Insert ERROR!!!!" << endl;
        cerr << "Either Value or Key was blank" << endl;
        cout << "Value = " << value << endl;
        cout << "key = " << key << endl;
        exit(1);
    }

}

/* remove()
 * ---
 * Input:   char*   
 * Output:  none
 * Return:  none
 * Big-O:   O(n) - Potentially could have to look in every slot for an opening. 
 *          Amortized O(1) if the hash function is low on clustering.
 * Notes:   Removes a whole Soundex set from the dictionary.
 */
void Hash::remove(char* key)
{
    (*lookup(key)).clear();
}

/* remove()
 * ---
 * Input:   char*, char*
 * Output:  none
 * Return:  none
 * Big-O:   O(n) - Potentially could have to look in every slot for an opening. 
 *          Amortized O(1) if the hash function is low on clustering.
 * Notes:   Removes a single word from the dictionary
 */
void Hash::removeWord(char* key, char* value)
{
    (*lookup(key)).remove(value);
}

/* find()
 * ---
 * Input:   char*, char*
 * Output:  none
 * Return:  bool
 * Big-O:   O(n) - Potentially could have to look in every slot for an opening. 
 *          Amortized O(1) if the hash function is low on clustering.
 * Notes:   Returns true if the word is in the dictionary, false otherwise.
 */
bool Hash::find(char* key, char* value)
{
    return (*lookup(key)).find(value);
}

/* lookup()
 * ---
 * Input:   char*, char*
 * Output:  none
 * Return:  List*
 * Big-O:   O(n) - Potentially could have to look in every slot for an opening. 
 *          Amortized O(1) if the hash function is low on clustering.
 * Notes:   Returns the list at the particular slot in the table.
 */
List* Hash::lookup(char* key)
{
    return table[findSlot(&*key)];
}

/* findSlot()
 * ---
 * Input:   char*
 * Output:  none
 * Return:  u_int
 * Big-O:   O(n) - Potentially could have to look in every slot for an opening. 
 *          Amortized O(1) if the hash function is low on clustering.
 * Notes:   Returns the slot number given by the hash of the key. 
 *          This uses Open Chaining to find an empty slot if a collision
 *          occurs. This is done by walking through the table until we find
 *          an open slot. The slot we return will either be empty, or it
 *          will contain the same key as the one given.
 */
u_int Hash::findSlot(char* key)
{
    u_int i = hashish(key) % TABLE_SIZE;
    
    while((!(*table[i]).empty()) && 
          (strncasecmp((*table[i]).getSoundex(), key, strlen(key))))
        i = (i + 1) % TABLE_SIZE;

    return i;
}


#if 0 
// Tackle this later when you know how to assign a vector
Hash::Hash(List* foo)
{
    // there might be a vector function that does this
    // for(u_int i = 0; i < TABLE_SIZE; ++i)
    table = foo;
}
#endif

/* Destructor
 * ---
 * Input:   char*
 * Output:  none
 * Return:  u_int
 * Big-O:   O(1) - Calls the vector.clear() method.
 */
Hash::~Hash(void)
{
    clear();
}

/* clear()
 * ---
 * Input:   void
 * Output:  none
 * Return:  void
 * Big-O:   O(1) - Calls the vector.clear() method.
 */
void Hash::clear(void)
{
    table.clear();
}

/* hashish()
 * ---
 * Input:   const char*
 * Output:  none
 * Return:  u_int
 * Big-O:   O(9n + 9) for n = 5. So, O(54), which is constant. 
 * Notes:   The algorithm used is the Jenkin One-At-A-Time hash. 
 * About:   Bob Jenkins' paper that accompanies his new lookup3.c algorithm
 *          has a study on the performance of various hash functions. He notes
 *          that selecting a good hash function is an art form, and it is
 *          wholly dependent on the application. That said, I chose his
 *          One-at-a-Time hash based on its simplicity, speed, and low
 *          collision rate. 
 *
 *          Speed: It takes 9n + 9 instructions to produce a hash
 *          value using OaaT. This is comparable to CRC, which uses 9n + 3.
 *          By comparison, Additive uses 5n + 3 and Universal uses 52n + 3.
 *
 *          Collisions: This is a very important factor in determining a hash
 *          function, because it can effect the speed more than the number of
 *          instructions. Jenkins tested this on a dictionary of 38,470 words
 *          and found 0 collisions with OaaT. By comparison, addive had 
 *          37,006 collisions. Rotating had 24, Burnstein's had 4, and Zobrist,
 *          Paul Hseih's, and MD4 had 1.
 *
 *          Reality: The dictionary I have been testing holds 98,569 words, 
 *          and I am running an AMD Turion 64 X2 Dual Core processor.
 *          The dictionary takes 4.529 real-time seconds to load. With a 
 *          reduced word-set (38,470), the time was 1.531 seconds. I found this
 *          to be acceptable, given the application's purpose.
 */
u_int Hash::hashish(const char* key) const
{
    ub4 h = 0;
    size_t i;
    // Note: SOUNDEX_LEN is the length of a soundex key (5).
    for(i = 0; i < SOUNDEX_LEN; ++i)
    {
        h += tolower(key[i]);
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return (h % TABLE_SIZE);
}
