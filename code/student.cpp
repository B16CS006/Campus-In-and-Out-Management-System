
#include <iostream>
#include <fstream>
#include <ctime>

#include "student.h"
#include "database.h"

#define specialPermissionfile "specialPermissionfile.txt"
#define studentfile "studentfile.txt"


using namespace std;

istream & operator>> (istream & in, Student & student){
    short _inside;
    in >> student.instituteId >> student.id >> student.name >> student.
    mobileNo >> student.inside;
    return in;
}

ostream & operator<< (ostream & out, Student & student){
    out << student.instituteId << " " << student.id << " " << student.
    name << " " << student.mobileNo << " " << student.inside << endl;
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////class function

Student::Student(){}

Student::Student (string _id, short _currentGateNo){
    ifstream file (studentfile, ios::in);
    Student student;
    while (file >> student){
        if (student.getInstituteId () == _id){
            id = student.id;
            name = student.name;
            mobileNo = student.mobileNo;
            inside = student.inside;
            instituteId = student.instituteId;
            currentGateNo = _currentGateNo;
            break;
        }
    }
}

Student::Student (string _instituteId, string _id, string _name, string _mobileNo, bool _inside){
    instituteId = _instituteId;
    id = _id;
    name = _name;
    mobileNo = _mobileNo;
    inside = _inside;
}

bool Student::isValidTime (){
    time_t currentTime = time(0);
    tm* now = localtime(&currentTime);
    if (now->tm_hour < 6 && now->tm_hour > 22 && now->tm_min >= 0 && now->tm_min <= 59)
        return false;
    else
        return true;
}

bool Student::checkSpecialPermission (){
    ifstream file (specialPermissionfile, ios::in);
    if (!file)
        return false;
    else{
        bool found = false;
        ofstream out ("tempSpecialPermissionfile.txt", ios::out);
        string id;
        while (file >> id){
            if (id == (*this).getInstituteId ()){
                found = true;
                break;
            }
            out << id << endl;
        }
        file.close ();
        out.close ();
        remove (specialPermissionfile);
        rename ("tempSpecialPermissionfile.txt", specialPermissionfile);
        if (found){
            cout << "\nSpecial Permission Found.\n";
            return true;
        }else{
            cout << "\nNo Special Permission Found.\n";
            return false;
        }
    }
}

void Student::addSpecialPermission (){
    ofstream file (specialPermissionfile, ios::app);
    file << (*this).getInstituteId () << endl;
    file.close ();
}

bool Student::entry (){
    if (isInside ()){
        cout << "\nInvalid, Student is already inside.\n";
        return false;
    }
    if (isValidTime ()){
        setGateNo (currentGateNo);
        flipInside ();
        Database_handler ().saveEntry (*this);
        return true;
    }else if (checkSpecialPermission ()){
        cout << "\nTime is Invalid But Student have Special Permission. So Allowed him/her.\n";
        setGateNo (currentGateNo);
        flipInside ();
        Database_handler ().saveEntry (*this);
        return true;
    }else{
        cout << "\nInvalid Time, No Special Permission. So provide him guest Room.\n";
        flipInside ();
        setGateNo (currentGateNo);
        Database_handler ().saveEntry (*this);
        return true;
    }
}

bool Student::exit (){
    if (!isInside ()){
        cout << "\nInvalid, Student is already outside.\n";
        return false;
    }
    if (isValidTime ()){
        setGateNo (currentGateNo);
        flipInside ();
        Database_handler ().saveEntry (*this);
        return true;
    }else if (checkSpecialPermission ()){
        cout << "\nTime is Invalid But Student have Special Permission. So Allowed him/her.\n";
        setGateNo (currentGateNo);
        flipInside ();
        Database_handler ().saveEntry (*this);
        return true;
    }else{
        cout << "\nInvalid Time and Not have Special permission. So Permission Denied.\n";
        return false;
    }
}

bool Student::exist (string _id){
    ifstream file (studentfile, ios::in);
    if (file){
        Student student;
        while (file >> student){
            if (student.instituteId == _id)
                return true;
        }
    }
    return false;
}
