
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>

#include "function.h"
#include "person.h"
#include "student.h"
#include "faculty.h"
#include "worker.h"
#include "vehicle.h"
#include "database.h"
#include "security.h"

using namespace std;

Security::Security (int _currentgateNo){
    setCurrentGateNo (_currentgateNo);
}

void Security::setCurrentGateNo (int newGateNo){
    if (newGateNo <= MAX_GATE && newGateNo >= MIN_GATE)
        currentGateNo = newGateNo;
    else{
        cout << "Such a Gate Number is not exist.\n\n\n";
    }
}

void Security::start (){
    while (true){
        system("clear");
        cout << "\n\nSecurity Home : " << currentGateNo << "\n\n";
        cout << "1--------> Add Entry\n";
        cout << "2--------> Add Exit\n";
        cout << "3--------> View Entries\n";
        cout << "4--------> Logout\n";
        cout << "\n\tChoose Option : ";
        char option = readChar();
        switch (option){
            case '1':
                addEntry ();
                Continue();
                break;
            case '2':
                addExit ();
                Continue();
                break;
            case '3':
                viewEntries ();
                Continue();
                break;
            case '4':
                logout ();
                return;
            case 's':{
                cout<<"\n<----Adding Special Permission---->\n";
                cout << "Enter Id : ";
                string id;
                id = readString();
                if (Student ().exist (id)){
                    cout << "\nSuccessfully changed.\n";
                    Student (id, currentGateNo).addSpecialPermission ();
                }else
                cout << "\nNo such Id found.\n";
                Continue();
                break;
            }
            case 'g':{
                cout<<"\n<----Changing Gate Number---->\n";
                cout << "Enter New Gate Number : ";
                int newGateNo;
                newGateNo = readInt(MIN_GATE,MAX_GATE);
                setCurrentGateNo (newGateNo);
                break;
            }
            default:
                cout << "\nInvalid\n";
                Continue();
        }
    }
}

bool Security::isVehicle (){
    cout << "Is Vehicle Present [y/n] : ";
    while(true){
        char isVehicle;
        isVehicle = readChar();
        if (isVehicle == 'Y' || isVehicle == 'y')
        return true;
        else if (isVehicle == 'N' || isVehicle == 'n')
            return false;
        else
            cout<<"\nInvalid\n\tTry again : ";
    }
}

void Security::addExit (){
    cout << "\n<----Add Exit---->\n";
    Database_handler database;
    if (isVehicle()){
        Vehicle vehicle (Vehicle ().addVehicle ());
        if (!vehicle.isInside ()){
            cout << "\nInvalid Entry, Vehicle is already outside.\n";
            return;
        }
        short color = vehicle.getColor ();
        if (color == 0)
            vehicle.setGateNo (currentGateNo);
        if (color == 2){
            cout << "\nBlack listed, Permission Denied.\n";
            return;
        }
        cout << "Enter Number of Person sitting inside : ";
        int noOfPerson;
        noOfPerson = readInt(1,50);
        vehicle.setNoOfPerson (noOfPerson);
        if (color == 1){
            int expectedGateNo = vehicle.getGateNo ();
            if (currentGateNo != expectedGateNo){
                cout << "\nExit is Not allowed through this gate. Try Gate Number : " << expectedGateNo << "\n";
                return;
            }
            vehicle.clearDues ();
        }
        cout << "Enter Details of each candidate sitting inside the vehicle.... \n\n";
        int validCandidate = 0;
        for (int i = 0; i < vehicle.getNoOfPerson (); i++){
            if (addPersonExit ())
                validCandidate++;
        }
        if (validCandidate){
            cout << "\nVehicle is allowed to exit.";
            vehicle.flipInside ();
            database.saveEntry (vehicle);
        }else{
            cout << "\nVehicle is not allowed to exit.\n";
            return;
        }
    }else{
        addPersonExit ();
    }
    cout<<"\n";
}

void Security::addEntry (){
    cout << "\n<----Add Entry---->\n";
    Database_handler database;
    if (isVehicle()){
        Vehicle vehicle (Vehicle ().addVehicle ());
        if (vehicle.isInside ()){
            cout << "\nInvalid Entry, Vehicle is already inside.\n";
            return;
        }
        int color = vehicle.getColor ();
        if (color == 2){
            cout << "\nBlack listed Vehicle. Permission denied.\n";
            return;
        }
        cout << "Enter Number of Person sitting inside : ";
        int noOfPerson;
        noOfPerson = readInt(1,50);
        vehicle.setNoOfPerson (noOfPerson);
        if (color == 1){			// different person come with different purpose in a same vehicle
            if (!vehicle.askPurpose ()){
                cout << "\aPermission Denied by Guard.\n";
                return;
            }
            if (!vehicle.checkVehiclePhysically ()){
                cout << "\nVehicle is not physically safe, Permission Denied.\n";
                return;
            }
            vehicle.setGateNo (currentGateNo);
        }
        int validCandidate = 0;
        for (int i = 0; i < vehicle.getNoOfPerson (); i++){
            if (addPersonEntry ())
                validCandidate++;
        }
        if (validCandidate){
            cout << "\nVehicle is allowed to enter.";
            vehicle.flipInside ();
            database.saveEntry (vehicle);
        }else{
            cout << "\nVehicle is not allowed to Enter.\n";
            return;
        }
    }else{
        addPersonEntry ();
    }
    cout<<"\n";
}

bool Security::addPersonExit (){
    cout << "\n<----Add Single Person Exit---->\n";
    bool allowed = false;
    string id;
    cout << "Enter ID : ";
    id = readString();
    PersonType person = checkId (id);
    Database_handler database;
    switch (person){
        case STUDENT:{
            Student student (id, currentGateNo);
            allowed = student.exit ();
            break;
        }
        case WORKER:{
            Worker worker (id, currentGateNo);
            allowed = worker.exit ();
            break;
        }
        case FACULTY:{
            Faculty faculty (id, currentGateNo);
            allowed = faculty.exit ();
            break;
        }
        case NON_INSTITUTE:{
            Person person (id, currentGateNo);
            allowed = person.exit ();
            break;
        }
        default:
            allowed = false;
    }
    if(allowed)
        cout<<"\nPerson is allowed to exit.";
    return allowed;
}

bool Security::addPersonEntry (){
    cout << "\n<----Add Single Person Entry---->\n";
    bool allowed = false;
    string id;
    cout << "Enter ID : ";
    id = readString();
    PersonType person = checkId (id);
    Database_handler database;
    switch (person){
        case STUDENT:{
            Student student (id, currentGateNo);
            allowed = student.entry ();
            break;
        }
        case WORKER:{
            Worker worker (id, currentGateNo);
            allowed = worker.entry ();
            break;
        }
        case FACULTY:{
            Faculty faculty (id, currentGateNo);
            allowed = faculty.entry ();
            break;
        }
        case NON_INSTITUTE:{
            Person person (id, currentGateNo);
            allowed = person.entry ();
            break;
        }
        default:
        allowed = false;
    }
    if(allowed)
        cout<<"\nPerson is allowed to enter.";
    return allowed;
}

PersonType Security::checkId (string _id){
//    cout << "\nChecking ID.....\n";
    if (Faculty ().exist (_id))
        return FACULTY;
    else if (Worker ().exist (_id))
        return WORKER;
    else if (Student ().exist (_id))
        return STUDENT;
    else if (!Person ().exist (_id))
        Person ().setDetail (_id);
    return NON_INSTITUTE;
}


void Security::viewEntries (){
    vector < Database_handler > list = Database_handler::getLogEntries ();
    for (int i = 0; i < list.size (); i++){
        if (list[i].getGateNo () != currentGateNo)
            list.erase (list.begin () + i--);
    }
    displaySingleEntry(list);
    if (selectBy ("Date")){
        short fd, fm, fy, td, tm, ty;
        cout << "Date Format : dd/mm/yyyy\n";
        cout << "From : ";
        string from = readString();
        if(!(from.size() == 10 && isdigit(from[0]) && isdigit(from[1]) && from[2] == '/' && isdigit(from[3]) && isdigit(from[4]) && from[5] == '/' && isdigit(from[6]) && isdigit(from[7]) && isdigit(from[8]) && isdigit(from[9]))){
            cout<<"\nThe format of Date is not match.\n";
            return;
        }
        stringstream ss;
        ss << from;
        char temp;
        ss >> fd >> temp >> fm >> temp >> fy;
        cout << "To : ";
        string to = readString();
        if(!(to.size() == 10 && isdigit(to[0]) && isdigit(to[1]) && to[2] == '/' && isdigit(to[3]) && isdigit(to[4]) && to[5] == '/' && isdigit(to[6]) && isdigit(to[7]) && isdigit(to[8]) && isdigit(to[9]))){
            cout<<"\nThe format of Date is not match.\n";
            return;
        }
        ss.clear();
        ss << to;
        ss >> td >> temp >> tm >> temp >> ty;
        if (!checkDate (fd, fm, fy, td, tm, ty)){
            cout << "\nFROM DATE is must be less than to TO DATE.\n";
            return;
        }
        for (int i = 0; i < list.size (); i++){
            if(!checkDate (fd, fm, fy, list[i].getDay (), list[i].getMonth (), list[i].getYear ())
               || !checkDate (list[i].getDay (), list[i].getMonth (), list[i].getYear (), td, tm, ty))
                list.erase (list.begin () + i--);
        }
        displaySingleEntry(list);
    }
    if (selectBy ("Time")){
        short fh, fm, th, tm;
        cout << "Time Format : hh:mm\n";// For not specifying enter 'none'\n";
        cout << "From : ";
        string from = readString();
        if(!(from.size() == 5 && isdigit(from[0]) && isdigit(from[1]) && from[2] == ':' && isdigit(from[3]) && isdigit(from[4]))){
            cout<<"\nThe format of Time is not match.\n";
            return;
        }
        stringstream ss;
        ss<<from;
        char temp;
        ss >> fh >> temp >> fm;
        cout << "To : ";
        string to = readString();
        if(!(to.size() == 5 && isdigit(to[0]) && isdigit(to[1]) && to[2] == ':' && isdigit(to[3]) && isdigit(to[4]))){
            cout<<"\nThe format of Time is not match.\n";
            return;
        }
        ss.clear();
        ss<<to;
        ss >> th >> temp >> tm;
        if (!checkTime (fh, fm, th, tm)){
            cout << "\nFROM TIME is must be less than to TO TIME.\n";
            return;
        }
        for (int i = 0; i < list.size (); i++){
            if (!checkTime (fh, fm, list[i].getHr (), list[i].getMin ()) || !checkTime (list[i].getHr (), list[i].getMin (), th, tm))
                list.erase (list.begin () + i--);
        }
        displaySingleEntry(list);
    }
    if (selectBy ("Entry/Exit)")){
        cout << "1 -> Entry\n0 -> Exit\n\tEnter here : ";
        bool in;
        in = readInt(0,1);
        for (int i = 0; i < list.size (); i++){
            if (list[i].getIn () != in)
                list.erase (list.begin () + i--);
        }
        displaySingleEntry(list);
    }
    if (selectBy ("Vehicle/Person")){
        cout << "1 -> Vehicle\n0 -> Person\n\tEnter here : ";
        bool vehicle;
        vehicle = readInt(0,1);
        for (int i = 0; i < list.size (); i++){
            if (list[i].getVehicle () != vehicle)
                list.erase (list.begin () + i--);
        }
        displaySingleEntry(list);
    }
    if (selectBy ("Id/Plate Number")){
        cout << "Enter Id/Plate Number : ";
        string number;
        number = readString();
        for (int i = 0; i < list.size (); i++){
            if (list[i].getId () != number)
                list.erase (list.begin () + i--);
        }
        displaySingleEntry(list);
    }
}

void Security::logout (){
    currentGateNo = -1;
    unsigned int count = 2, dots = 4, mseconds = 200;
    mseconds *= 1000;
    cout<<"\n\n\tLogging out";
    while(count--){
        cout<<flush;
        for(int i = 0;i<dots;i++){
            usleep(mseconds);
            cout<<"."<<flush;
        }
        for(int i = 0;i<dots;i++){
            cout<<"\b \b";
        }
    }
}

void Security::displaySingleEntry(const vector<Database_handler> &list)const{
    cout<<"\n                               History Gate "<<currentGateNo<<"\n";
    cout<<"----------------------------------------------------------------------------\n";
    if(list.size()==0){
        cout<<"Result Not Found.\n\n";
        return;
    }
    cout<<"Date\t\tTime\t      Entry/Exit    Vehicle/Person\tID\n";
    cout<<"----------------------------------------------------------------------------\n";
    for(int i=0;i<list.size();i++){
        cout<<list[i].getDay()<<"/"<<list[i].getMonth()<<"/"<<list[i].getYear()<<"\t"<<list[i].getHr()<<":"<<list[i].getMin()<<"\t\t";
        if(list[i].getIn())
            cout<<"Entry";
        else
            cout<<"Exit";  
        if(list[i].getVehicle())
            cout<<"\t\tVehicle\t\t";
        else
            cout<<"\t\tPerson\t\t";
        cout<<list[i].getId()<<endl;
    }
}
