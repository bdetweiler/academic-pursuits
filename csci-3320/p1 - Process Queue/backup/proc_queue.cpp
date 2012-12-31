/*
 * proc_queue.cpp
 * By Brian Detweiler
 */

#include<stdio.h>
#include<fstream>
#include<errno.h>

#include"dheap.h"
#include"process.h"

#define BUF_LEN	256

const char* DELIM = " \t\n\r\0";

void help(const char* prog_name, u_int err);
// char** strtoker(const char*, const char*);
long strtolong(const char*, const char*);

int main(int argc, char* argv[])
{
    // Initialize our heap
    Heap<Process*> h;
    h.set_d(2);

    // The name of this program
    char* prog_name = argv[0];
    // Pointer to the file we are opening
    // FILE* file; 
    // A character pointer to a buffer of data read from file
    char buf[BUF_LEN];
    // Pre-definition of "d" in d-heap
    int d = 2;
    // The path to the file provided as the 
    // 1st argument when the program is run
    const char* path = "";
    u_int time_units;
    /* 
     * Pieces of a process. Note, they are
     * longs instead of ints, because we are 
     * using strtol() instead of atoi() for error checking
     */
    long enterTime;
    long priorityLevel;
    long timeUntilComplete;
    char* programName;


    // If they only supplied a file name
    if(argc == 2)
    {
        //path = argv[1];
        help(prog_name, 1);
    }
    // If they supplied a file name AND the number of time units
    else if(argc == 3)
    {
        path = argv[1];
        time_units = atoi(argv[2]);
        if(time_units <= 0)
            help(prog_name, 5);
    }
    // If they supplied a file name AND the number of time units
    // AND a "d" for the heap
    else if(argc == 4)
    {
        path = argv[1];
        time_units = atoi(argv[2]);
        if(time_units <= 0)
            help(prog_name, 5);
        d = atoi(argv[2]);
        // d can't be less than 2.
        if(d < 2)
            help(prog_name, 4);
    }
    // If they fucked up their arguments altogether
    else
    {
        help(prog_name, 1);
    }

    // Open the file in a stream for reading
    ifstream file(path);

    // If the file opened
    if(file)
    {
        // Flag to let us know when we pushed a process on the heap
        bool pushedOnHeap = false;
        // While our time has not run out
        for(u_int time = 0; time < time_units; ++time)
        {
            cout << "time = " << time << ' ';
            // Time starts at 0
            // If the time has arrived
            if(time == 0 || pushedOnHeap)
            {
                // Get a line from the file
                file.getline(buf, sizeof(buf));
                // If our file is still valid 
                // i.e. we haven't hit EOF yet
                if(file)
                {
                    // Put together the pieces of our process
                    char* str;

                    // enterTime
                    str = strtok(buf, DELIM);
                    enterTime = strtolong(str, prog_name);
                    
                    // priorityLevel
                    str = strtok(NULL, DELIM);
                    priorityLevel = strtolong(str, prog_name);

                    // timeUntilComplete
                    str = strtok(NULL, DELIM);
                    timeUntilComplete = strtolong(str, prog_name);

                    // programName
                    programName = strtok(NULL, "\0");
                }
                // Reset the heap flag
                pushedOnHeap = false;
            }
            // If it's time to enter our last read process
            if(enterTime == time)
            {
                // Push it on the heap
                cout << "inserting  " << programName << ' ';
                h.insert(new Process(priorityLevel, timeUntilComplete,
                                     enterTime, programName));
                pushedOnHeap = true;
            }
            // If our heap isn't empty, we need to run a process
            if(!h.empty())
            {
                Process *p = h.remove_root();
                p->set_insertion_time(time);
                cout << "running  " << p->get_proc_name() << ' ';
                p->set_time_left(p->get_time_left() - 1);
                // If our process isn't done, push it back on the heap
                if(!p->done())
                    h.insert(p);
                else
                    cout << "finished ";
            }
            cout << endl;
        }
        // We're done with our file stream
        file.close();
    }
    else
    {
        // Close the failed file stream and give an error
        file.close();
        help(prog_name, 2);
    }

    return(0);
}

/*
 * strtolong
 * ---
 * Input: const char* str, const char* prog_name
 * Output: None
 * Return: long
 * Notes:  Wrapper function for strtol(). Turns a char* into a long integer,
 *         and unlike atoi(), does error checking.
 */
long strtolong(const char* str, const char* prog_name)
{

    char* endptr; 
    long rval;
    // Defined in errno.h
    errno = 0;
    rval = strtol(str, &endptr, 10);

    if((errno == ERANGE && (rval == LONG_MAX || rval == LONG_MIN))
        || (errno != 0 && rval == 0))
    {
        help(prog_name, 3);
    }
    if(endptr == str)
    {
        help(prog_name, 3);
    }
    return rval;
}

/*
 * help
 * ---
 * Input:  const char* prog_name, u_int err
 * Output: Error messages
 * Return: void
 * Note:   Gives various error messages dependant on err, 
 *         and exits gracefully.
 */
void help(const char* prog_name, u_int err)
{
    cerr << "Error!" << endl;
    switch(err)
    {
        case 1:
            cerr << "Usage: " << prog_name << " input_file time_units [ d-heap number ] " << endl;
            break;
        case 2:
            cerr << "No such file! Check the file name and try again." << endl;
            break;
        case 3:
            cerr << "Bad values! Check your input file!" << endl;
            break;
        case 4:
            cerr << "Invalid d-heap! Your d-heap must be 2 or greater." << endl;
            break;
        case 5:
            cerr << "Invalid time! Your time units must be greater than 0!" << endl;
            break;
        default:
            cerr << "Usage: " << prog_name << " [ input file ] [ d-heap number ] " << endl;
    }
    exit(err);
}
