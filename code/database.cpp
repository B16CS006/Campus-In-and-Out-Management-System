
#include <iostream>
#include <fstream>
#include <ctime>

#include "database.h"

#define logfile "logfile.txt"
#define personfile "personfile.txt"
#define studentfile "studentfile.txt"
#define facultyfile "facultyfile.txt"
#define workerfile "workerfile.txt"
#define vehiclefile "vehiclefile.txt"

using namespace std;

istream & operator>> (istream & input, Database_handler & database){
    input >> database.gateNo >> database.day >> database.month >> database.
    year >> database.hr >> database.min >> database.in >> database.
    id >> database.vehicle;
    return input;
}

ostream & operator<< (ostream & output, Database_handler & database){
    output << database.gateNo << " " << database.day << " " << database.
    month << " " << database.year << " " << database.hr << " " << database.
    min << " " << database.in << " " << database.id << " " << database.
    vehicle << endl;
    return output;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////class function

Database_handler::Database_handler(){}

Database_handler::Database_handler (short _gateNo, bool _in, string _id, bool _vehicle){
    day = 19;
    month = 3;
    year = 2018;
    hr = 9;
    min = 0;
    gateNo = _gateNo;
    in = _in;
    id = _id;
    vehicle = _vehicle;
}

short Database_handler::getGateNo ()const{
    return gateNo;
}

short Database_handler::getDay ()const{
    return day;
}

short Database_handler::getMonth ()const
{
    return month;
}

short Database_handler::getYear ()const
{
    return year;
}

short Database_handler::getHr ()const{
    return hr;
}

short Database_handler::getMin ()const{
    return min;
}

bool Database_handler::getIn ()const{
    return in;
}

string Database_handler::getId ()const{
    return id;
}

bool Database_handler::getVehicle ()const{
    return vehicle;
}

void Database_handler::saveEntry (Person person){
    Database_handler (person.getGateNo (), person.isInside (),
        person.getId ()).addLogEntry ();
    ifstream file (personfile, ios::in);
    if (!file){
        ofstream out (personfile, ios::out);
        out << person;
        out.close ();
        return;
    }else{
        ofstream out ("tempPersonfile.txt", ios::out);
        Person temp;
        while (file >> temp){
            if (temp.getId () == person.getId ())
                continue;
            out << temp;
        }
        out << person;
        file.close ();
        out.close ();
        remove (personfile);
        rename ("tempPersonfile.txt", personfile);
    }
}

void Database_handler::saveEntry (Student student){
    Database_handler (student.getGateNo (), student.isInside (),
        student.getInstituteId ()).addLogEntry ();
    ifstream file (studentfile, ios::in);
    if (!file){
        ofstream out (studentfile, ios::out);
        out << student;
        out.close ();
        return;
    }else{
        ofstream out ("tempStudentfile.txt", ios::out);
        Student temp;
        while (file >> temp){
            if (temp.getInstituteId () == student.getInstituteId ())
                continue;
            out << temp;
        }
        out << student;
        file.close ();
        out.close ();
        remove (studentfile);
        rename ("tempStudentfile.txt", studentfile);
    }
}

void Database_handler::saveEntry (Worker worker){
    Database_handler (worker.getGateNo (), worker.isInside (),
        worker.getInstituteId ()).addLogEntry ();
    ifstream file (workerfile, ios::in);
    if (!file){
        ofstream out (workerfile, ios::out);
        out << worker;
        out.close ();
        return;
    }else{
        ofstream out ("tempWorkerfile.txt", ios::out);
        Worker temp;
        while (file >> temp){
            if (temp.getInstituteId () == worker.getInstituteId ())
                continue;
            out << temp;
        }
        out << worker;
        file.close ();
        out.close ();
        remove (workerfile);
        rename ("tempWorkerfile.txt", workerfile);
    }
}

void Database_handler::saveEntry (Faculty faculty){
    Database_handler (faculty.getGateNo (), faculty.isInside (),
        faculty.getInstituteId ()).addLogEntry ();
    ifstream file (facultyfile, ios::in);
    if (!file){
        ofstream out (facultyfile, ios::out);
        out << faculty;
        out.close ();
        return;
    }else{
        ofstream out ("tempFacultyfile.txt", ios::out);
        Faculty temp;
        while (file >> temp){
            if (temp.getInstituteId () == faculty.getInstituteId ())
                continue;
            out << temp;
        }
        out << faculty;
        file.close ();
        out.close ();
        remove (facultyfile);
        rename ("tempFacultyfile.txt", facultyfile);
    }
}

void Database_handler::saveEntry (Vehicle vehicle){
    Database_handler (vehicle.getGateNo (), vehicle.isInside (), vehicle.getPlateNo (),1).addLogEntry ();
    ifstream file (vehiclefile, ios::in);
    if (!file){
        ofstream out (vehiclefile, ios::out);
        if(vehicle.isInside())
            out << vehicle;
        out.close ();
        return;
    }else{
        ofstream out ("tempVehiclefile.txt", ios::out);
        Vehicle temp;
        while (file >> temp){
            if (temp.getPlateNo () == vehicle.getPlateNo ())
                continue;
            out << temp;
        }
        if(vehicle.isInside())
            out << vehicle;
        file.close ();
        out.close ();
        remove (vehiclefile);
        rename ("tempVehiclefile.txt", vehiclefile);
    }
}

void Database_handler::addLogEntry (){
    time_t currentTime = time(0);
    tm* now = localtime(&currentTime);
    ofstream file (logfile, ios::app);
    file<<gateNo<<" "<<now->tm_mday<< " "<<1+now->tm_mon<<" "<<1900+now->tm_year<<" "<<now->tm_hour<<" "<<now->tm_min<<" "<<in<<" "<<id<<" "<<vehicle<<"\n";
//    file << (*this);
    file.close ();
}

std::vector<Database_handler> Database_handler::getLogEntries (){
    std::vector < Database_handler > list;
    ifstream file (logfile, ios::in);
    if (file){
        Database_handler database;
        while (file >> database){
            list.push_back (database);
        }
        file.close ();
    }
    return list;
}
