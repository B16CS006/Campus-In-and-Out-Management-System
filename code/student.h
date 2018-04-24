#ifndef STUDENT_H
#define STUDENT_H

#include "institute_member.h"

class Student:public Institute_member{
public:
    Student();
    Student (std::string, short);
    Student (std::string, std::string, std::string, std::string, bool _inside = true);
    
    bool isValidTime ();
    bool checkSpecialPermission ();
    void addSpecialPermission ();
    bool entry ();
    bool exit ();
    bool exist (std::string _id);
    
    friend std::istream & operator>> (std::istream &, Student &);
    friend std::ostream & operator<< (std::ostream &, Student &);
};

#endif
