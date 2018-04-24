
#include <iostream>
#include <fstream>

#include "faculty.h"
#include "database.h"

#define facultyfile "facultyfile.txt"


using namespace std;

istream & operator>> (istream & in, Faculty & faculty){
    in >> faculty.instituteId >> faculty.id >> faculty.name >> faculty.
    mobileNo >> faculty.inside;
    return in;
}

ostream & operator<< (ostream & out, Faculty & faculty){
    out << faculty.instituteId << " " << faculty.id << " " << faculty.
    name << " " << faculty.mobileNo << " " << faculty.inside << endl;
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////class function

Faculty::Faculty(){}

Faculty::Faculty (string _id, short _currentGateNo){
    ifstream file (facultyfile, ios::in);
    Faculty faculty;
    while (file >> faculty){
        if (faculty.getInstituteId () == _id){
            id = faculty.id;
            name = faculty.name;
            mobileNo = faculty.mobileNo;
            inside = faculty.inside;
            instituteId = faculty.instituteId;
            currentGateNo = _currentGateNo;
            break;
        }
    }
}

Faculty::Faculty (string _instituteId, string _id, string _name, string _mobileNo, bool _inside){
    instituteId = _instituteId;
    id = _id;
    name = _name;
    mobileNo = _mobileNo;
    inside = _inside;
}

bool Faculty::entry (){
    if (isInside ()){
        cout << "\nInvalid, Faculty is already inside.\n";
        return false;
    }
    setGateNo (currentGateNo);
    flipInside ();
    Database_handler ().saveEntry (*this);
    return true;
}

bool Faculty::exit (){
    if (!isInside ()){
        cout << "\nInvalid, Faculty is already outside.\n";
        return false;
    }
    setGateNo (currentGateNo);
    flipInside ();
    Database_handler ().saveEntry (*this);
    return true;
}

bool Faculty::exist (string _id){
    ifstream file (facultyfile, ios::in);
    if (file){
        Faculty faculty;
        while (file >> faculty){
            if (faculty.instituteId == _id)
                return true;
        }
    }
    return false;
}
