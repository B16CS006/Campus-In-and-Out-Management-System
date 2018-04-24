
#include <iostream>
#include <fstream>

#include "worker.h"
#include "database.h"

#define workerfile "workerfile.txt"


using namespace std;

istream & operator>> (istream & in, Worker & worker)
{
    in >> worker.instituteId >> worker.id >> worker.name >> worker.
    mobileNo >> worker.inside;
    return in;
}

ostream & operator<< (ostream & out, Worker & worker)
{
    out << worker.instituteId << " " << worker.id << " " << worker.
    name << " " << worker.mobileNo << " " << worker.inside << endl;
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////class function

Worker::Worker(){}

Worker::Worker (string _id, short _currentGateNo){
    ifstream file (workerfile, ios::in);
    Worker worker;
    while (file >> worker){
        if (worker.getInstituteId () == _id){
            id = worker.id;
            name = worker.name;
            mobileNo = worker.mobileNo;
            inside = worker.inside;
            instituteId = worker.instituteId;
            currentGateNo = _currentGateNo;
            break;
        }
    }
}

Worker::Worker (string _instituteId, string _id, string _name, string _mobileNo, bool _inside){
    instituteId = _instituteId;
    id = _id;
    name = _name;
    mobileNo = _mobileNo;
    inside = _inside;
}

bool Worker::entry (){
    if (isInside ()){
        cout << "\nInvalid, Worker is already inside.\n";
        return false;
    }
    setGateNo (currentGateNo);
    flipInside ();
    Database_handler ().saveEntry (*this);
    return true;
}

bool Worker::exit (){
    if (!isInside ()){
        cout << "\nInvalid, Worker is already outside.\n";
        return false;
    }
    setGateNo (currentGateNo);
    flipInside ();
    Database_handler ().saveEntry (*this);
    return true;
}

bool Worker::exist (string _id){
    ifstream file (workerfile, ios::in);
    if (file){
        Worker worker;
        while (file >> worker){
            if (worker.instituteId == _id)
                return true;
        }
    }
    return false;
}
