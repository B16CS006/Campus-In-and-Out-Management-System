
#include <iostream>
#include <fstream>

#include "vehicle.h"
#include "function.h"

#define vehiclefile "vehiclefile.txt"
#define registeredVehiclefile "registeredVehiclefile.txt"


using namespace std;


istream & operator>> (istream & in, Vehicle & vehicle){
    short _color, _inside;
    in >> vehicle.plateNo >> vehicle.noOfPerson >> vehicle.
    gateNo >> _color >> _inside;
    if (_color == 0)
        vehicle.color = GREEN;
    else if (_color == 2)
        vehicle.color = BLACK;
    else
        vehicle.color = RED;
    vehicle.inside = _inside;
    return in;
}

ostream & operator<< (ostream & out, const Vehicle & vehicle){
    out << vehicle.plateNo << " " << vehicle.noOfPerson << " " << vehicle.
    gateNo << " " << vehicle.color << " " << vehicle.inside << endl;
    return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////class functions

Vehicle::Vehicle(){}

Vehicle::Vehicle (string _plateNo, int _noOfPerson, int _gateNo,
    VehicleColor _color, bool _inside){
    plateNo = _plateNo;
    noOfPerson = _noOfPerson;
    gateNo = _gateNo;
    color = _color;
    inside = _inside;
}

Vehicle::Vehicle (string _plateNo){
    ifstream file (vehiclefile, ios::in);
    Vehicle vehicle;
    while (file >> vehicle){
        if (vehicle.plateNo == _plateNo){
            *this = vehicle;
            break;
        }
    }
    file.close ();
    color = isRegistered ();
}

Vehicle & Vehicle::operator = (const Vehicle & vehicle){
    plateNo = vehicle.plateNo;
    noOfPerson = vehicle.noOfPerson;
    gateNo = vehicle.gateNo;
    color = vehicle.color;
    inside = vehicle.inside;
    return *this;
}

string Vehicle::getPlateNo (){
    return plateNo;
}

void Vehicle::setPlateNo (string _plateNo){
    plateNo = _plateNo;
}

int Vehicle::getNoOfPerson (){
    return noOfPerson;
}

void Vehicle::setNoOfPerson (int _noOfPerson){
    noOfPerson = _noOfPerson;
}

bool Vehicle::isInside (){
    return inside;
}

void Vehicle::setInside (bool _inside){
    inside = _inside;
}

void Vehicle::flipInside (){
    inside = !inside;
}

VehicleColor Vehicle::getColor (){
    return color;
}

int Vehicle::getGateNo (){
    return gateNo;
}

int Vehicle::setGateNo (int _gateNo){
    gateNo = _gateNo;
}

void Vehicle::setColor (short _color){
    switch (_color){
        case 0:
        color = GREEN;
        break;
        case 1:
        color = RED;
        break;
        case 2:
        color = BLACK;
        break;
        default:
        color = RED;
    }
}

string Vehicle::getPurpose (){
    return purpose;
}

bool Vehicle::askPurpose (){
    cout << "Enter Purpose : ";
    purpose = readString(true);
    cout << "Valid Purpose [y/n] : ";
    char validate;
    while(true){
        validate = readChar();
        if (validate == 'Y' || validate == 'y')
            return true;
        if(validate == 'n' || validate == 'N')
            return false;
        cout <<"\nInvalid\n\tTry again : ";
    }
}

VehicleColor Vehicle::isRegistered (){
    ifstream file (registeredVehiclefile, ios::in);
    if (!file)
        return RED;
    string _plateNo;
    short _color;
    while (file >> _plateNo >> _color){
        if (plateNo == _plateNo)
            return (VehicleColor) _color;
    }
    return RED;
}

bool Vehicle::exist (string _plateNo){
    ifstream file (vehiclefile, ios::in);
    if (file){
        Vehicle vehicle;
        while (file >> vehicle){
            if (vehicle.plateNo == _plateNo){
                (*this) = vehicle;
                file.close ();
                return true;
            }
            file.close ();
        }
        return false;
    }
}

string Vehicle::addVehicle (){
    cout << "Enter Plate Number : ";
    plateNo = readString();
    if (exist (plateNo)){
        return plateNo;
    }
    noOfPerson = 0;
    color = isRegistered ();
    if (color == GREEN)
        inside = true;
    else
        inside = false;
    ofstream file (vehiclefile, ios::app);
    file << (*this);
    file.close ();
    return plateNo;
}

bool Vehicle::checkVehiclePhysically (){
    cout << "Is Vehicle is physically safe [y/n] : ";
    while(true){
        char safe = readChar();
        if (safe == 'y' || safe == 'Y')
            return true;
        if(safe == 'n' || safe == 'N')
            return false;
        cout<<"\nInvalid\n\tTry again : ";
    }
}

void Vehicle::clearDues (){
    cout << "Dues Clear.";
}
