#include <iostream>
#include <fstream>

#include "account.h"
#include "function.h"

using namespace std;

#define accountfile "accountfile.txt"

istream & operator>> (istream & in, Account_Handler & account){
    short _type;
    in >> account.username >> account.password >> _type;
    if (_type == 0)
        account.type = NOONE;
    if (_type == 1)
        account.type = SECURITY;
    else
        account.type = ADMIN;
    return in;
}

ostream & operator<< (ostream & out, const Account_Handler & account){
    out << account.username << " " << account.password << " " << account.type << "\n";
    return out;
}

///////////////////////////////////////////////////////////////////////class Functions

Account_Handler::Account_Handler (){
    username = "noone";
    password = "noone";
    type = SECURITY;
}

Account_Handler::Account_Handler (string _username, string _password, UserType _type){
    username = _username;
    password =_password;
    type=_type;
}

string Account_Handler::getUsername (){
    return username;
}

void Account_Handler::setPassword (string _password){
    password = _password;
}

bool Account_Handler::checkExistence (string _username){
    ifstream file (accountfile, ios::in);
    if (!file){
        cout << "\nFile not found.\n";
        return false;
    }else{
        Account_Handler account;
        while (file >> account){
            if (_username == account.getUsername ()){
                file.close();
                return true;
            }
        }
        file.close ();
    }
    return false;
}

void Account_Handler::showPassword(string _username){
	ifstream file(accountfile,ios::in);
	if(file){
		Account_Handler account;
		while(file>>account){
			if(_username == account.getUsername()){
				file.close();
				cout<<"\nPassowrd : "<<account.password<<endl;
				return;
			}
		}
		file.close();
	}
	cout<<"\nNo Such User Found.\n";
}

void Account_Handler::addNewUserAccount (string _username, string _password){
    ofstream file (accountfile, ios::app);
    if (!file)
        cout << "\nFile not found.\n";
    else
    {
        Account_Handler account (_username, _password, SECURITY);
        file << account << endl;
        cout << "\nNew User Successful Added.\n";
        file.close ();
    }
}

void Account_Handler::changePassword (string newPassword){
    if (!checkFileExistence (accountfile)){
        cout << "\nFile not found.\n";
        return;
    }
    ifstream in (accountfile, ios::in);
    ofstream out ("tempAccountfile.txt", ios::out);
    bool found = false;
    Account_Handler account;
    while (in >> account){
        if (username == account.getUsername ()){
            account.setPassword (newPassword);
            found = true;
        }
        out << account;
    }
    in.close ();
    out.close ();
    remove (accountfile);
    rename ("tempAccountfile.txt", accountfile);
    if (found)
        cout << "\nPassword Successfully Changed.\n";
    else
        cout << "\nPassword not Changed.\n\tUsername not found.\n";
}

UserType Account_Handler::verify (){
//    cout << "\nVerifying Account ......\n\n";
    ifstream file (accountfile, ios::in);
    if (!file){
        cout << "\nFile not found.\n";
        cout << "\n\n\tGenerating New Username and Password.\n";
        ofstream file (accountfile, ios::out);
        Account_Handler account ("admin", "abc123", ADMIN);
        file << account;
        account = Account_Handler ("gaurd", "123abc", SECURITY);
        file << account;
        file.close ();
        return NOONE;
    }else{
        Account_Handler account;
        while (!file.eof ()){
            file >> account;
            if (account.username == username && account.password == password)
                return type = account.type;
        }
    }
    return NOONE;
}

bool Account_Handler::removeAccount (){
    if (!checkFileExistence (accountfile)){
        cout << "\nFile not found.\n";
        return false;
    }
    ifstream in (accountfile, ios::in);
    ofstream out ("tempAccountfile.txt", ios::out);
    bool found = false;
    Account_Handler account;
    while (in >> account){
        if (account.getUsername () == username && account.type == SECURITY){
        	found = true;
            continue;
        }
        out << account << endl;
    }
    in.close ();
    out.close ();
    remove (accountfile);
    rename ("tempAccountfile.txt", accountfile);
    if (found){
        cout << "\nSuccessfully remove.\n";
        return true;
    }
    else{
        cout << "\nAction not allowed.\n";
        return false;
    }
}

