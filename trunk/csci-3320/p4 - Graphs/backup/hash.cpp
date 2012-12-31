#include"hash.h"

/* setDebug()
 * ---
 * input:   bool
 * output:  none
 * return:  void
 * time:    O(1)
 * notes:   Sets the debug option. 
 */
void Hash::setDebug(bool d)
{
    debug = d;
}

/* Hash()
 * ---
 * Default Constructor
 *
 * Time:    O(n) - n = TABLE_SIZE = 260000.
 *          We have to set up all the vector* and all the lists.
 * Notes:   Builds a hash table using a vector<List*>
 */
Hash::Hash(void)
{ 
    debug = false;

    if(debug)
        cout << "table_size = " << TABLE_SIZE << endl;

    // if(debug)
        // cout << "old_table_size = " << old_table_size << endl;

    // Have to set up our table by creating the lists first
    for(u_int i = 0; i < TABLE_SIZE; ++i)
    {
        table.push_back(new vector<List*>());
        (*table.back()).push_back(new List());
    }
}

/* getTable(void)
 * ---
 * input:   none
 * output:  none
 * return:  vector<List*>
 * time:    O(1)
 * notes:   Returns the actual table which is a vector of list pointers.
 */
vector<vector<List*>*> Hash::getTable(void)
{
    return table;
}

/* insert(char*, char*)
 * ---
 * input:   char*, char* bool
 * output:  none
 * return:  void
 * time:    O(n) - This is where Big-O is deceptive. Our worst-case is that 
 *          our hash function sucks and keeps sending us to the same damn 
 *          spot every time. So we would have to search down every 
 *          vector<List*> for the right soundex. Thankfully, our hash 
 *          function does not suck. 
 * amort.:  O(1) - In one example, I ran a dictionary of 98569 words and
 *          had 325 collisions. 325 / 98569 = 0.3% collision rate. Not bad.
 * notes:   Insert a value into the hash table
 *          If newInsert is true, the value will be added to the oldTable.
 *          If it's false, we're just resizing the table and we don't want
 *          to have duplicate entries in oldTable
 */
void Hash::insert(char* key, char* value)
{

    if(debug)
        cout << "insert(" 
             << key 
             << ", " 
             << value 
             << ")" 
             << endl;

    // If the input values are not empty, 
    // Add the second condition if we don't want dupes
    if(!*value || !*key) // && !find(key, value))
    {
        cout << "Hash Insert ERROR!!!!" << endl;
        cout << "Value = " << value << endl;
        cout << "key = " << key << endl;
        exit(1);
    }
    
    List* tmp = lookup(key);
   
    // Resetting the soundex each time won't hurt anything, and it
    // is not adding to our big-O, because checking to see if it is
    // NULL each time would actually be more work.
    (*tmp).setSoundex(key);
    (*tmp).insert(value);

    if(debug)
        cout << "End of insert()" << endl;
}


/* remove()
 * ---
 * input:   char*
 * output:  none
 * return:  none
 * time:    O(n^2) - Again, worst case for lookup is O(n), but
 *          this is not the case in reality because we have a good 
 *          hash function.
 * amort.:  O(n) - lookup() is O(1) and clear() on a vector is O(n).
 * notes:   Removes a whole Soundex set from the dictionary
 */
void Hash::remove(char* key)
{
    (*lookup(key)).clear();
}

/* removeWord()
 * ---
 * input:   char*, char*
 * output:  none
 * return:  none
 * time:    O(nm) - where n = number of soundex codes, 
 *                  and m = number of words in the given soundex code
 * amort:   O(m) - lookup is O(1) amortized time, so the list function
 *                 remove() will likely cost more time than lookup
 * notes:   Removes a word from the dictionary
 */
void Hash::removeWord(char* key, char* value)
{
    (*lookup(key)).remove(value);
}

/* find()
 * ---
 * input:   char*, char*
 * output:  none
 * return:  bool
 * time:    O(n) - See lookup for details
 * amort.:  O(1) - See lookup for details
 * notes:   Finds a value given a key
 */
bool Hash::find(char* key, char* value)
{
    if(debug)
        cout << "find(" << key << ", " << value << ")" << endl;
    return (*lookup(key)).find(value);
}

/* lookup(char*)
 * ---
 * input:   char*
 * output:  none
 * return:  List*
 * time:    O(n) - This is absolute worst case, and never likely
 *          to actually happen. 
 * amort.:  O(1) - The amortized time on this is constant because
 *          the collision rate is so low, we are highly unlikely
 *          to ever have to search through all the lists. 
 * notes:   Returns the list of words for a soundex key, or a blank
 *          List if the spot is empty.
 */
List* Hash::lookup(char* key)
{
    List* rval = NULL;

    if(debug)
        cout << "lookup(" << key << ") = " << hashish(key) << endl;

    u_int pos = hashish(key);

    // (*table[pos]) gives us a vector<List*>
    // There is always a list in each slot. If the first list is empty though,
    // we'll have to check it and any others to see if the soundex matches
    if((*(*table[pos])[0]).size() > 0)
    {

        for(u_int i = 0; i < (*table[pos]).size() && !rval; ++i)
        {
            if(debug)
                cout << "strncmp(" 
                     << (*(*table[pos])[i]).getSoundex()
                     << ", " << key << ", " <<  SOUNDEX_LEN << ") = " 
                     << strncmp((*(*table[pos])[i]).getSoundex(), key, SOUNDEX_LEN)
                     << endl;

            // If the soundex keys match, we'll return this list
            if(strncmp((*(*table[pos])[i]).getSoundex(), key, SOUNDEX_LEN) == 0)
                rval = ((*table[pos])[i]);
        }

        // If we didn't find a matching soundex, 
        // we'll push back a new list and return that
        if(!rval)
        {
            // Can use this to count collisions
            if(debug)
                cout << "COLLISION @ " << pos << " on key " << key << endl;

            ((*table[pos]).push_back(new List()));
            rval = (*table[pos]).back();
        }
    }
    // There's only one list.
    // If that one list is not empty
    else if(!((*(*table[pos])[0]).empty()))
    {
        if(debug)
            cout << "getSoundex() = " << (*(*table[pos])[0]).getSoundex() << endl;
        // If the soundex matches, we'll return this list
        if(strncmp((*(*table[pos])[0]).getSoundex(), key, SOUNDEX_LEN) == 0)
            rval = (*table[pos]).back();
        // If not, we need to push back another list and return that
        else
        {
            if(debug)
                cout << "COLLISION @ " << pos << " on key " << key << endl;

            (*table[pos]).push_back(new List());
            rval = (*table[pos]).back();
        }
    }
    // It's empty. Return the only list in the vector
    else
        rval = (*table[pos]).back();
   
    return rval;
}


/* Destructor
 * ---
 * Input:   void
 * Output:  none
 * Return:  none
 * Time:    O(n) - Vector clear is linear time. 
 * Notes:   Cleans up when we're done with the class
 */
Hash::~Hash(void)
{
    clear();

    // Since we dynamically allocated the array, we need to free it
    // free(primeList);
}

/* clear()
 * ---
 * Input:   void
 * Output:  none
 * Return:  void
 * Time:    O(n) - Vector clear is linear time. 
 * Notes:   Clears the entire table using the vector.clear() function.
 */
void Hash::clear(void)
{
    table.clear();
}

/* hashish()
 * ---
 * Input:   char* 
 * Output:  None
 * Return:  u_int
 * Time:    O(1) - Note: This is not the number of computations done.
 *          But since we can always calculate the number, 
 *          we say it is constant time.
 * Notes:   The algorithm used is the Bob Jenkins One-At-A-Time hash.
 */
u_int Hash::hashish(const char* key) const
{
    if(debug)
        cout << "hashish(" << key << ")" << endl;
    ub4 h = 0;
    size_t i;

    for(i = 0; i < SOUNDEX_LEN; ++i)
    {
        h += key[i];
        h += (h << 10);
        h ^= (h >> 6);
    }
    
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
   
    if(debug)
        cout << "hashish(): returning: " << h % TABLE_SIZE << endl;

    return (h % TABLE_SIZE);
}
