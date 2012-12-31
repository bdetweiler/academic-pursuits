#ifndef HASH_H
#define HASH_H

#include<string.h>
#include<iostream>
#include<vector>
using namespace std;

#include"list.h"

typedef unsigned long int  ub4;
typedef unsigned      char ub1;

// Number of spots we need in the hash table is 1040
// [A-Z][0-9][0-9][0-9][0-9] == 26 * 10 * 10 * 10 * 10 == 260,000

#define TABLE_SIZE 260000

// Length of a soundex code: Z0000
#ifndef SOUNDEX_LEN
#define SOUNDEX_LEN 5
#endif
#define hashsize(n) ((ub4)1<<(n)) 
#define hashmask(n) (hashsize(n)-1) 

// Change this to false for Perfect Hashing
// #define OPEN_ADDRESSING false

class Hash
{
    public:
        // return a short list of candidates
        const char* find(const char* str) const;
        void add(const char* str, const char* id);
        
        // Should set all lists to NULL
        Hash(void);

        // Create hash table from existing hash table
        Hash(List*);
        ~Hash(void);

        u_int findSlot(char*);
        void insert(char*, char*);
        void remove(char*);
        void removeWord(char*, char*);
        List* lookup(char*);
        bool find(char*, char*);
        vector<List*> getTable(void);
        void clear(void);
        // the hashing function
        u_int hashish(const char*) const;
        // u_int hashish(char*, u_int);

    private:
        // a vector of Lists to hold the hashed dictionary
        vector<List*> table;
};
#endif
