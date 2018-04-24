#ifndef SECURITY_H
#define SECURITY_H

#include <vector>

enum PersonType{ STUDENT, FACULTY, WORKER, NON_INSTITUTE };

class Security{
public:
  Security (int);

  void start ();
  PersonType checkId (std::string);

  void displaySingleEntry(const std::vector < Database_handler > & )const;
  void setCurrentGateNo(int);
  bool isVehicle ();
  void addEntry ();
  void addExit ();
  void viewEntries ();
  void logout ();
private:
    int currentGateNo;
    bool addPersonEntry ();
    bool addPersonExit ();
};

#endif
