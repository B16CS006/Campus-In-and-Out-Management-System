#ifndef DATABSAE_H
#define DATABASE_H

#include <vector>

#include "person.h"
#include "student.h"
#include "faculty.h"
#include "worker.h"
#include "vehicle.h"

class Database_handler{
public:
    Database_handler();
    Database_handler (short _gateNo, bool _in, std::string _id, bool _vehicle = false);
    
    short getGateNo ()const;
    short getDay ()const;
    short getMonth ()const;
    short getYear ()const;
    short getHr ()const;
    short getMin ()const;
    bool getIn ()const;
    std::string getId ()const;
    bool getVehicle ()const;
/*
    void setGateNo (short);
    void setDay (short);
    void setMonth (short);
    void setYear (short);
    void setHr (short);
    void setMin (short);
    void setIn (bool);
    void setId (string);
*/
    void saveEntry (Person);
    void saveEntry (Student);
    void saveEntry (Worker);
    void saveEntry (Faculty);
    void saveEntry (Vehicle);
    
    void addLogEntry ();
    
    static std::vector < Database_handler > getLogEntries ();
    
    friend std::istream & operator>> (std::istream &, Database_handler &);
    friend std::ostream & operator<< (std::ostream &, Database_handler &);
private:
    short gateNo;
    short day, month, year;
    short hr, min;
    bool in;
    std::string id;
    bool vehicle;
};

#endif
