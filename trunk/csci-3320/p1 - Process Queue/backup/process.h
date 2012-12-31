/*
 * process.h
 * By Brian Detweiler
 */

#ifndef PROCESS_H
#define PROCESS_H
#include<string>
#include<iostream>
using namespace std;

typedef unsigned int u_int;

class Process
{
    private:
        u_int priority_level;
        u_int time_left;
        u_int insertion_time;
        string proc_name;
    public:
        Process(void) : priority_level(0), time_left(0), insertion_time(0), 
                        proc_name("") { }
        //Process(Process&);
        Process(const Process&);
        Process(int pl, int tl, int it, const char* pn) : priority_level(pl), 
                        time_left(tl), insertion_time(it), proc_name(pn) { }
        ~Process(void);

        bool done(void);
        void set_priority_level(u_int);
        void set_time_left(u_int);
        void set_insertion_time(u_int);
        void set_proc_name(string);

        const u_int get_priority_level(void);
        const u_int get_time_left(void);
        const u_int get_insertion_time(void);
        const string get_proc_name(void);

        // This is what we use to compare the Processes
        const u_int get_effective_priority(void);

        // Operator Overloading
        bool operator < (Process&);
        bool operator > (Process&);
        bool operator <= (Process&);
        bool operator >= (Process&);
        bool operator == (Process&);
        bool operator != (Process&);
       
     // friend ostream & operator << (ostream&, const Rat&);
        friend ostream & operator << (ostream&, const Process&);
};

#endif
