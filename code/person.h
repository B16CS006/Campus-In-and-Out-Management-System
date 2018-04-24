#ifndef PERSON_H
#define PERSON_H

class Person{
public:
    Person();
    Person (std::string _id, short _currentGateNo);
    Person (std::string _id, std::string _name, std::string _mobileNo, bool _inside = false);

    std::string getId ();
    std::string getName ();
    std::string getMobileNo ();
    void setId (std::string);
    void setName (std::string);
    void setMobileNO (std::string);
    bool isInside ();
    void setInside (bool);
    int getGateNo ();
    void setGateNo (int);
    void flipInside ();
    
    void setDetail (std::string);
    bool askPurpose ();
    
    virtual bool entry ();
    virtual bool exit ();
    virtual bool exist (std::string);
    
    friend std::istream & operator>> (std::istream &, Person &);
    friend std::ostream & operator<< (std::ostream &, const Person &);
protected:
    std::string id;
    std::string name;
    std::string mobileNo;
    bool inside;
    int gateNo;
    std::string purpose;
    int currentGateNo;
};

#endif
