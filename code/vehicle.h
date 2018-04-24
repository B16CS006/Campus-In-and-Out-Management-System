#ifndef VEHICLE_H
#define VEHICLE_H

enum VehicleColor{ GREEN, RED, BLACK };

class Vehicle{
public:
    Vehicle();
    Vehicle (std::string _plateNo);
    Vehicle (std::string, int, int, VehicleColor _color = RED, bool _inside = false);
    
    Vehicle & operator = (const Vehicle &);
    
    std::string getPlateNo ();
    void setPlateNo (std::string);
    int getNoOfPerson ();
    void setNoOfPerson (int);
    bool isInside ();
    void setInside (bool);
    void flipInside ();
    VehicleColor getColor ();
    void setColor (short);
    int getGateNo ();
    int setGateNo (int);
    
    std::string getPurpose ();
    bool askPurpose ();
    
    VehicleColor isRegistered ();
    bool exist (std::string);
    std::string addVehicle ();
    bool checkVehiclePhysically ();
    
    void clearDues ();
    
    friend std::istream & operator>> (std::istream &, Vehicle &);
    friend std::ostream & operator<< (std::ostream &, const Vehicle &);
private:
    std::string plateNo;
    int noOfPerson;
    int gateNo;
    VehicleColor color;
    bool inside;
    std::string purpose;
};

#endif
