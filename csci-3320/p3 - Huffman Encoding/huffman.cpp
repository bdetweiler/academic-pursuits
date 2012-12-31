/*****************************************************************************
 * Authors:     John W. Clark && Brian Detweiler                             *
 * Filename:    huffman.cpp                                                  *
 * Description: Main file for huffman encoder                                *
 * ************************************************************************* */

#include<iostream>
using namespace std;

#include"config.h"

#include"codes.h"

#define HELP_ERROR 99

// WARNING: Global variables!
bool verbose = false;
bool debug = false;

#define VERBOSE  if(verbose)
#define DEBUG   if(debug)

void usage_msg(const string& pname)
{
    cerr << "Usage: " << pname << " : valid flags are :" << endl
        << " -i input_file  : required" << endl
        << " -o output_file : required" << endl
        << " -e  : turn on encoding mode (default)" << endl
        << " -d  : turn on decoding mode" << endl
        << " -v  : verbose mode" << endl
        << " -vv : very verbose mode" << endl
        << " -h  : this help screen" << endl;
}

int main(int argc, char* argv[])
{
    string in_name;
    string out_name;

    bool encode = true;

    for(int i = 1; i < argc; ++i)
    {
        // If the help flag was passed
        if(!strncmp("-h", argv[i], strlen(argv[i])) || !strncmp("--help", argv[i], strlen(argv[i])))
        {
            usage_msg(argv[0]);
            exit(HELP_ERROR);
        }
        else if(!strncmp("-i", argv[i], strlen(argv[i])) && (argc > i + 1))
        {
            cerr << "input file is '" << argv[++i] << "'" << endl;
            in_name = argv[i];
        }
        else if(!strncmp("-o", argv[i], strlen(argv[i])) && (argc > i + 1))
        {
            cerr << "output file is '" << argv[++i] << "'" << endl;
            out_name = argv[i];
        }
        else if(!strncmp("-d", argv[i], strlen(argv[i])))
        {
            encode = false;
        }
        else if(!strcmp("-e", argv[i]))
        {
            encode = true;
        }
        else if(!strcmp("-v", argv[i]))
        {
            verbose = true;
        }
        else if(!strncmp("-vv", argv[i], 3))
        {
            verbose = true;
            debug = true;
        }

    }

    if(!in_name.size() || !out_name.size())
    {
        cerr << "input and output file are required, nothing to do!" << endl;
        usage_msg(argv[0]);
        exit(HELP_ERROR);
    }
   
    // Check to see if input file exists
    ifstream fileExist(in_name.c_str(), ios::in | ios::binary);

    if(!fileExist)
    {
        cerr << "File '" << in_name << "' not found!" << endl;
        exit(HELP_ERROR);
    }
    fileExist.close();

// If the NO_OVERWRITE config option is enabled, the default action is
// to ask before overwriting an output file.
#if NO_OVERWRITE
    fileExist.open(out_name.c_str(), ios::in | ios::binary);

    char overwrite;

    if(fileExist)
    {
        while(toupper(overwrite) != 'Y' && toupper(overwrite) != 'N')
        {
            cerr << "\nThe destination file, " << out_name << " exists. Overwrite? (Y/N): ";
            cin >> overwrite;
            if(toupper(overwrite) == 'N')
            {
                cerr << "Aborted! Try using a different file name." << endl << endl;
                fileExist.close();
                exit(HELP_ERROR);
            }
        }

        fileExist.close();
    }
#endif

    Codes codes;

    if(encode)
    {
        cerr << "Encoding " << in_name << " -> " << out_name << endl;
        codes.encode(in_name, out_name);
    }
    else
    {
        cerr << "Decoding " << in_name << " -> " << out_name << endl;
        codes.decode(in_name, out_name);
    }

    cerr << "done .... " << endl;
    return 0;
}


