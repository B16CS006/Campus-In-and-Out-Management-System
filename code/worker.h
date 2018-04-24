#ifndef WORKER_H
#define WORKER_H

#include "institute_member.h"

class Worker:public Institute_member{
public:
    Worker();
    Worker (std::string, short);
    Worker (std::string, std::string, std::string, std::string, bool _inside = true);
    
    bool entry ();
    bool exit ();
    bool exist (std::string);
    
    
    friend std::istream & operator>> (std::istream &, Worker &);
    friend std::ostream & operator<< (std::ostream &, Worker &);
};

#endif
