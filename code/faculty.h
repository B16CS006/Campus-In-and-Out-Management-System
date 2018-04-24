#ifndef FACULTY_H
#define FACULTY_H

#include "institute_member.h"

class Faculty:public Institute_member{
public:
    Faculty();
    Faculty (std::string, short);
    Faculty (std::string, std::string, std::string, std::string, bool _inside = true);
    
    bool entry ();
    bool exit ();
    bool exist (std::string _id);
    
    friend std::istream & operator>> (std::istream &, Faculty &);
    friend std::ostream & operator<< (std::ostream &, Faculty &);
};

#endif
