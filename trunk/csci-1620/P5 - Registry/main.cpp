/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    main.cpp                                                        * 
 * Use:     Driver class that acts as a registry program. Read, write, and  *
 *          query a registry of name/value pairs. 
 ****************************************************************************/

#include<iostream>
using namespace std;

#include"list.h"

#include<iomanip>
#include<fstream>

void del(Word, List &);                 // DELETE
void query(const Word, const List &);   // QUERY
void assign(Word, Word, List &);        // ASSIGN
void parseLine(char *, List::List&);    // parse each entry

/* Input:   A Word and a List &
 * Output:  "DELETE name = 'name'"
 * Return:  None
 * Notes:   Function for deleting registry entries.
 */
void del(Word name, List &list)
{
    cout << "DELETE name = '"
         << name
         << '\''
         << endl;
    list.remove(name);
}

/* Input:   A constant Word and a List &
 * Output:  "QUERY name = 'name' value = 'value'"
 * Return:  None
 * Notes:   Function for querying registry entries.
 */
void query(const Word name, const List &list)
{
    cout << "QUERY name = '"  
         << name             
         << "' value = '"    
         << list.find(name)  
         << '\''             
         << endl;
}

/* Input:   A Word, A Word, and a List &
 * Output:  "ASSIGN name = 'name' value = 'value'"
 * Return:  None
 * Notes:   Function for inserting registry name/value pairs.
 */
void assign(Word name, Word value, List &list)
{
cout << "INSERTING" << endl;
    list.insert(name, value);
    cout << "ASSIGN name = '" 
         << name 
         << "' value = '"
         << list.find(name) // value
         << '\''
         << endl;
}



/* Input:   A char * and a List &
 * Output:  "DELETE name = name"
 * Return:  None
 * Notes:   Function used for deleting registry entries.
 */
// A line looks like this:
// name1 name2=value blah blah blah
void parseLine(char *line, List &list)
{
    char *ptr; 
   
    // Assignment
    if((ptr = strchr(line, '=')))
    {
        Word name  = strtok(line, " \t="); // Get the first token
        Word value = ptr + 1;              // The char * to the right of ptr
        assign(name, value, list);         // Insert name/value pair
    }
    // Query
    else if((ptr = strchr(line, '?')))
    {
        Word name = ptr + 1;               // The char * to the right of ptr
        query(name, list);                 // Query the name/value pair
    }
    // Print
    else if((ptr = strchr(line, '@')))
    {
        cout << "PRINT" << endl;
        cout << list << endl;              // Calls overloaded << operator
    }
    // Delete
    else if((ptr = strchr(line, '-')))
    {
        Word name = ptr + 1;               // The char * to the right of ptr
        del(name, list);                   // Delete the value from 'name'
    }
    else
    {
        // Anything else is an invalid command
        cout << "Unrecognized command" << endl;
    }
}

int main(int argc, char *argv[])
{
    Word word;
    List list;

    if(argc < 2)
    {
        // No argument given
        cout << "Usage " << argv[0] << " <file>" << endl;
        exit(1);
    }
    /************************************************************************
     * Begin istream. If the file doesn't exist, there's nothing to do.     *
     * Proceed to take user input. If the file does exist, read from it and *
     * store the contents input into a list. Then take user input.          *
     ************************************************************************/
    ifstream in;
    ofstream out;
    in.open(argv[1], ios_base::in); // Open registry file for reading
    
    // If the file does not exist
    if(in.fail())
    {
        in.close();
        // Reset ios bit
        in.clear(ios::failbit);
        // Skip parsing through anything
    }
    else
    {
        // File exists. Open it and read from it.

        // line stores input from the registry file
        char line[256];
        // While not end of file
        while(in.getline(line, 256))
        {   
            // Parse the registry line by line
            // and store it into a list
            parseLine(line, list);
        }
        in.close();
    }
    
    /************************************************************************
     * Begin ostream. Take user input and modify the list's contents.       *
     * Upon finishing, write the contents of the list to the file, and      *
     * close the file.                                                      *
     ************************************************************************/

    // input stores user input
    char input[256];
    // Read user input and perform requested operations
    while(cin.getline(input, 255)) // while input != EOF
    {
        parseLine(input, list);
    }
   
    // Open the file for writing
    out.open(argv[1], ios_base::out);

    // Write list to file.
    out << list;
    // Close file
    out.close();
    // Print the list
    cout << list << endl;
    return 0;
}

