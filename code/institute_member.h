#ifndef INSTITUTE_MEMBER_H
#define INSTITUTE_MEMBER_H

#include "person.h"

class Institute_member:public Person{
public:
    Institute_member ();
    Institute_member (std::string);
    
    std::string getInstituteId ();
    void setInstituteId (std::string);
protected:
    std::string instituteId;
};

#endif
