#ifndef ACCOUNT_H
#define ACCOUNT_H

enum UserType{ NOONE, SECURITY, ADMIN };

class Account_Handler{
public:
  Account_Handler ();
  Account_Handler (std::string, std::string, UserType _type = SECURITY);

  std::string getUsername ();
  void setPassword (std::string);
  bool checkExistence (std::string);
  void addNewUserAccount (std::string, std::string);
  void changePassword (std::string);
  UserType verify ();
  bool removeAccount ();
  void showPassword(std::string);

  friend std::istream & operator>> (std::istream &, Account_Handler &);
  friend std::ostream & operator<< (std::ostream &, const Account_Handler &);

private:
  std::string username;
  std::string password;
  UserType type;
};

#endif
