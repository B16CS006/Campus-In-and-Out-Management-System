#ifndef ADMIN_H
#define AMIN_H

#include <vector>

class Admin{
public:
  void start ();
  void addNewUserAccount ();
  void showPassword();
  void viewEntries ();
  void logout ();
private:
  void removeUser ();
  void changeUserPassword ();
  void displaySingleEntry(const std::vector<Database_handler> &)const;
};

#endif
