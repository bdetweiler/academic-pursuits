/*****************************************************************************
 * Author:      Brian Detweiler                                              *
 * Filename:    codes.h                                                      *
 * Description: Header file for codes class                                  * 
 * ************************************************************************* */

#include"dheap.h"
#include"tree.h"
#include"config.h"

// For file descriptors
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

// For strings
#include<string>

// For assert
#include<assert.h>

// For  reading files and 
#include<fstream>

// For printing
#include<iostream>

// For memory functions
#include<cstdlib>
using namespace std;


// EXIT CODES
#define BADBIN 1
#define BADSTRINGSIZE 2

#ifndef TABLE_SIZE
#define TABLE_SIZE 256
#endif

#define IN_FILE_LEN 256
// Size of malloc'd code in binToChrPtr()
#define CODE_SIZE 512
#define BYTE_LEN 8
#define REALLOC_SIZE 2

// Number of bytes needed to store the tree size
// (One byte for the char, one for the '\0')
#define CHAR_SIZE_BUF 2

// Number of bytes it takes to represent the tree size
#define TREE_SIZE_BYTES 2

// Error message for a larger compressed file than input file
#define LARGER_OUT_FILE 112358
// Declared and set in huffman.cpp
extern bool verbose;
extern bool debug;

#define VERBOSE  if(verbose)
#define DEBUG    if(debug)

class Codes
{
    private:
        Heap<Tree*> heap;
        Tree tree;
       
        u_char key;
        u_char value;

        // The binary representation of the tree
        string treeCode;

        // The binary string retrieved from the Huffman-encoded file
        string codeIn;

        // Size of the input file
        size_t inFileSize;
        size_t outFileSize;

        // How much the file was compressed
        float compressionRatio;

        void exportTree(const char*);
        u_int importTree(const char*);

        // Code sizes
        size_t treeSize;
        size_t codeSize;

        // Pad sizes
        size_t treePadSize;
        size_t codePadSize;

        char* binToCharPtr(string, bool);

    public:
        Codes(void)
            {;;;}

        void decode(string, string);
        void encode(string, string);

};
