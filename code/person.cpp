
#include <iostream>
#include <fstream>

#include "person.h"
#include "function.h"
#include "database.h"

#define personfile "personfile.txt"

using namespace std;

istream & operator>> (istream & in, Person & person){
    in >> person.id >> person.name >> person.mobileNo >> person.
    inside >> person.gateNo;
    return in;
}

ostream & operator<< (ostream & out, const Person & person){
    out << person.id << " " << person.name << " " << person.
    mobileNo << " " << person.inside << " " << person.gateNo << endl;
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////class function

Person::Person(){}

Person::Person (string _id, string _name, string _mobileNo, bool _inside){
    id = _id;
    name = _name;
    mobileNo = _mobileNo;
    inside = _inside;
}

Person::Person (string _id, short _currentGateNo){
    ifstream file (personfile, ios::in);
    Person person;
    while (file >> person){
        if (person.getId () == _id){
            id = person.id;
            name = person.name;
            mobileNo = person.mobileNo;
            inside = person.inside;
            gateNo = person.gateNo;
            currentGateNo = _currentGateNo;
            break;
        }
    }
}

string Person::getId (){
    return id;
}

string Person::getName (){
    return name;
}

string Person::getMobileNo (){
    return mobileNo;
}

void Person::setId (string _id){
    id = _id;
}

void Person::setName (string _name){
    name = _name;
}

void Person::setMobileNO (string _mobileNo){
    mobileNo = _mobileNo;
}

bool Person::isInside (){
    return inside;
}

void Person::setInside (bool _inside){
    inside = inside;
}

int Person::getGateNo (){
    return gateNo;
}

void Person::setGateNo (int _gateNo){
    gateNo = _gateNo;
}

void Person::flipInside (){
    inside = !inside;
}

void Person::setDetail (string _id){
    cout << "\nAdding New Person to Database\n";
    cout << "Enter Person Details : \n\n";
    id = _id;
    cout << "Enter Name : ";
    name = readString(true);
    for(int i = 0;i<name.size();i++)
        if(name[i] == ' ')
            name[i] = '_';
    cout << "Enter Mobile Number : ";
    while(true){
        mobileNo = readString();
        if(checkMobileNo(mobileNo))
            break;
        else
            cout<<"\nInvalid\n\tTry again : ";
    }
    gateNo = 0;
    inside = false;
    ofstream file (personfile, ios::app);
    file << (*this);
    file.close ();
}

bool Person::askPurpose (){
    cout << "Enter Purpose : ";
    purpose = readString(true);
    char valid;
    cout << "Valid Purpose or not [y/n] : ";
    while(true){
        valid = readChar();
        if (valid == 'Y' || valid == 'y')
            return true;
        if(valid == 'n' || valid == 'N')
            return false;
        cout << "\nInvalid\n\tTry again : ";
    }
}


bool Person::entry (){
    if (inside){
        cout << "\nInvalid, Person is already inside.\n";
        return false;
    }
    if (!askPurpose ()){
        cout << "\nInvalid Purpose, can't allowed.\n";
        return false;
    }
    setGateNo (currentGateNo);
    flipInside ();
    Database_handler ().saveEntry (*this);
    return true;
}

bool Person::exit (){
    if (!inside){
        cout << "\nInvalid, Person is already outside.\n";
        return false;
    }
    int expectedGateNo = getGateNo ();
    if (currentGateNo != expectedGateNo){
        cout << "\nPerson's exit is not allowed through this gate. Try Gate Number : " <<
        expectedGateNo<<"\n";
        return false;
    }
    flipInside ();
    Database_handler ().saveEntry (*this);
    return true;
}

bool Person::exist (string _id){
    ifstream file (personfile, ios::in);
    if (file){
        Person person;
        while (file >> person){
            if (person.id == _id)
                return true;
        }
    }
    return false;
}
