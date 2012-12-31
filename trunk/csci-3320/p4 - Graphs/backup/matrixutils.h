/****************************************************************************
 * Author:  Brian Detweiler                                                 *
 * File:    graphutils.h                                                    *
 * Use:     Utilities for the Graph class. Mostly for printing  and display *
 *          purposes. Also provides conversion functions.                   *
 ***************************************************************************/

#define ITOA_OFFSET 48

string numToString(u_int);
string cell(string, size_t, size_t = 0, string = "center");
string cell(int, size_t, size_t = 0, string = "center");
u_int stringToNum(string);
char itoa(const int);
string reverseStr(string);


typedef long unsigned int u_long;
typedef unsigned int u_int;

string cell(string foo, size_t printCellSize, size_t padding, string alignment)
{
    if(alignment == "left")
        // Now we'll "streatch" the cell on each side
        for(size_t i = 0; foo.size() < printCellSize; ++i)
            foo = foo + " ";

    else if(alignment == "right")
        for(size_t i = 0; foo.size() < printCellSize; ++i)
            foo = " " + foo;
    else if(alignment == "center")
    {
        // If foo's size is an odd number, less than the max size,
        // add a space to even it out.
        if(foo.size() % 2 && foo.size() < printCellSize)
            foo = " " + foo;
        // Now we'll "streatch" the cell on each side
        for(size_t i = 0; foo.size() < printCellSize; ++i)
            foo = " " + foo + " ";
    }

    return foo;
}


string cell(int foo, size_t printCellSize, size_t padding, string alignment)
{ return cell(numToString(static_cast<u_int>(foo)), printCellSize, padding); }

// converts a single digit int to it's ASCII representation
char itoa(const int num)
{
    int rval = -1;
    if(num >= 0 && num < 10)
        rval = num + ITOA_OFFSET;

    return rval;
}

string reverseStr(string s)
{
    size_t size = s.size();
    string rval = "";
    for(size_t i = 0; i < size; ++i)
    {
        rval += s.substr(s.size() - 1, s.size());
        s = s.substr(0, s.size() - 1);
    }
    return rval;
}

// Converts an unsigned int to a string
string numToString(u_int num)
{
    string rval = "";

    do
    {
        if(num < 10)
            rval.push_back(itoa(num));
        else
            rval.push_back(itoa((num - ((int)(num * 0.1) * 10))));

        num = ((int)(num * 0.1));
    }while(num > 0);
    return reverseStr(rval);
}

u_int stringToNum(string s)
{
    return atoi(s.c_str());
}
