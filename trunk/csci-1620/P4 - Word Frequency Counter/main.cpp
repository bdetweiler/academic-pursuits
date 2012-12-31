/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    main.cpp                                                        * 
 * Use:     Utilizes class List and class Word to parse through a text      *
 *          file and count the number of times a word appears.              *
 ****************************************************************************/

#include<iostream>
using namespace std;

#include"list.h"

#include<fstream>

int main(int argc, char *argv[])
{
    Word word;
    List list;

    if(argc < 2)
    {
        // No argument given
        cout << "Usage " << argv[0] << " <file>" << endl;
        return 1;
    }
    // Open the file
    ifstream file(argv[1]);
   
    // The line that stores the characters
    char line[256];
    // Delimiters: tells where the word begins and ends. 
    const char *delim = " \t.,!@#$%^&*()+\"[];";
    // While not end of file
    while(file.getline(line, 256))
    {
        char *tok = strtok(line, delim);
        // Assign the current char * to a Word
        word = tok;
        // Insert the first word in the list
        list.insert(word);
        // Loop through the rest of the line
        while((tok = strtok(NULL, delim)))
        {
            word = tok;
            list.insert(word);
        }
    }
    // Print the list
    cout << list << endl;
    return 0;
}

