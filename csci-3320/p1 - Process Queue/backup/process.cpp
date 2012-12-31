/*
 * process.cpp
 * By Brian Detweiler
 */

#include"process.h"
/*
Process::Process(Process &foo)
{

    this->priority_level = foo.get_priority_level();
    this->time_left = foo.get_time_left();
    this->insertion_time = foo.get_insertion_time();
    this->proc_name = foo.get_proc_name();
}
*/
Process::Process(const Process &foo)
{

    this->priority_level = foo.priority_level;
    this->time_left = foo.time_left;
    this->insertion_time = foo.insertion_time;
    this->proc_name = foo.proc_name;
}

Process::~Process(void)
{
    this->priority_level = 0;
    this->time_left = 0;
    this->insertion_time = 0;
    this->proc_name = "";
}

bool Process::done(void)
{
    bool rval = false;
    if(time_left <= 0)
        rval = true;
    return rval;
}

void Process::set_priority_level(u_int pl)
{
    this->priority_level = pl;
}

void Process::set_time_left(u_int tl)
{
    this->time_left = tl;
}

void Process::set_insertion_time(u_int it)
{
    this->insertion_time = it;
}

void Process::set_proc_name(string name)
{
    this->proc_name = name;
}

const u_int Process::get_priority_level(void)
{
    return this->priority_level;
}

const u_int Process::get_time_left(void)
{
    return this->time_left;
}

const u_int Process::get_insertion_time(void)
{
    return this->insertion_time;
}

const string Process::get_proc_name(void)
{
    return this->proc_name;
}

const u_int Process::get_effective_priority(void)
{
    return this->priority_level + this->insertion_time;
}

bool Process::operator < (Process& p)
{
    return this->get_effective_priority() < p.get_effective_priority();
}

bool Process::operator > (Process& p)  
{
    return this->get_effective_priority() > p.get_effective_priority();
}

bool Process::operator <= (Process& p)
{
    return this->get_effective_priority() <= p.get_effective_priority();
}

bool Process::operator >= (Process& p)
{
    return this->get_effective_priority() >= p.get_effective_priority();
}

bool Process::operator == (Process& p)
{
    return this->get_effective_priority() == p.get_effective_priority();
}

bool Process::operator != (Process& p)
{
    return this->get_effective_priority() != p.get_effective_priority();
}

ostream &operator << (ostream &ost, const Process &p)
{
    ost << p.insertion_time << " " << p.priority_level << " "
        << p.time_left << " " << p.proc_name;
    return ost;
}    
