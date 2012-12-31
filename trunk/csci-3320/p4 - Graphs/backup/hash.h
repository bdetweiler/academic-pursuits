#ifndef HASH_H
#define HASH_H

#include<string.h>
#include<iostream>
#include<cassert>
#include<string>
#include<vector>
using namespace std;

#include"list.h"

typedef unsigned long int  ub4;
typedef unsigned      int  u_int;
typedef unsigned      char ub1;

#define hashsize(n) ((ub4)1<<(n)) 
#define hashmask(n) (hashsize(n)-1) 

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
        vector<vector<List*>*> getTable(void);
        void clear(void);
        // the hashing function
        u_int hashish(const char*) const;
        // u_int hashish(char*, u_int);
        void setDebug(bool);

    private:
        // a vector of Lists to hold the hashed dictionary
        vector<vector<List*>*> table;
        
        bool debug;

        // List of primes upto MAGIC_NUMBER ^ 2
        // This will grow quickly, so we should only have to 
        // run getNextPrime a few times.
        // bool* primeList;

        // Gotta keep this around so we always know the array len
        // u_int primeListLen;

        // Current size of the table, wich will be a prime
        // u_int table_size;
        
        // Current size of the table, wich will be a prime
        // u_int old_table_size;
       
        // Get the next prime after table_size
        // u_int getNextPrime(void);
        
        // Get the next prime after table_size
        // void primeSeive(void);

        // Just clears table, so we keep the old data in oldTable 
        // so we can resize and reinsert
        // void clearTable(void);
        
        // Resizes the hash table
        // void resize(void);

};
#endif
