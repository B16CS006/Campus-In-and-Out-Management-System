
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>

#include "function.h"
#include "account.h"
#include "database.h"
#include "admin.h"

using namespace std;


void Admin::start (){
    while (true){
        system("clear");
        cout << "\n\nAdmin Home\n\n";
        cout << "1--------> Add New Account\n";
        cout << "2--------> Remove Account\n";
        cout << "3--------> Change Password\n";
        cout << "4--------> View Entries\n";
        cout << "5--------> Logout\n";
        cout << "\n\tChoose Option : ";
        char option;
        option = readChar();
        switch (option){
            case '1':
                addNewUserAccount ();
                Continue();
                break;
            case '2':
                removeUser ();
                Continue();
                break;
            case '3':
                changeUserPassword ();
                Continue();
                break;
            case '4':
                viewEntries ();
                Continue();
                break;
            case '5':
                logout ();
                return;
            case 's':
                showPassword();
                Continue();
                break;
            default:
                cout << "\nInvalid Key\n";
                Continue();
        }
    }
}

void Admin::showPassword(){
    cout <<"\n<----Showing Password---->\n";
    string _username,_adminUsername,_adminPassword;
    cout << "Enter Username : ";
    _username = readString();
    cout << "Enter Admin Username : ";
    _adminUsername = readString();
    cout << "Enter Admin Password : ";
    _adminPassword = takePassword();
    Account_Handler account(_adminUsername,_adminPassword);
    if(account.verify())
        account.showPassword(_username);
    else
       cout << "\nInvalid Username or Password\n";
    return;
}

void Admin::removeUser (){
    cout << "\n<----Removing User---->\n";
    string _username, _password;
    cout << "Enter Username : ";
    _username = readString();
    cout << "Enter Password : ";
    _password = takePassword ();
    Account_Handler account (_username, _password);
    if (account.verify ())
        account.removeAccount ();
    else
        cout << "\nNo such User Found.\n";
}

void Admin::changeUserPassword (){
    cout << "\n<----Changing User Password---->\n";
    string username, password;
    cout << "Enter Username : ";
    username = readString();
    cout << "Enter Password : ";
    password = takePassword ();
    Account_Handler account (username, password);
    bool user = account.verify ();
    if (user == false){
        cout << "\nINVALID Username and Password.";
        return;
    }else{
        string newPassword;
        cout << "Enter New Password : ";
        newPassword = takePassword ();
        cout << "Confirm Password : ";
        password = takePassword ();
        if (newPassword == password){
            account.changePassword (password);
        }else{
            cout << "\nPassword Doesn't Confirm.\n";
        }
    }
}

void Admin::addNewUserAccount (){
    cout << "\n<----Adding New User Account---->\n";
    string username, password, conPassword;
    cout << "Enter New Username : ";
    username = readString();
    Account_Handler account;
    if (account.checkExistence (username)){
        cout << '\n' << username <<" is already exist.\n\n";
        return;
    }
    cout << "Enter New Password : ";
    password = takePassword ();
    cout << "Confirm Password : ";
    conPassword = takePassword ();
    if (password == conPassword){
        account.addNewUserAccount (username, password);
    }else{
        cout << "\nPassword Doesn't Confirm.\n";
    }
}

void Admin::logout (){
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

void Admin::viewEntries (){
    vector < Database_handler > list = Database_handler::getLogEntries ();	
    displaySingleEntry(list);
    if (selectBy ("Gate Number")){
        cout<<"Enter Gate Number : ";
        short gateNumber;
        gateNumber = readInt(MIN_GATE,MAX_GATE);
        for (int i = 0; i < list.size (); i++){
            if (list[i].getGateNo () != gateNumber)
                list.erase (list.begin () + i--);
        }
        displaySingleEntry(list);
    }
    if (selectBy ("Date")){
        short fd, fm, fy, td, tm, ty;
        cout << "Date Format : dd/mm/yyyy\n";
        cout << "From : ";
        string from = readString();
        if(!(from.size() == 10 && isdigit(from[0]) && isdigit(from[1]) && from[2] == '/' && isdigit(from[3]) && isdigit(from[4]) && from[5] == '/' && isdigit(from[6]) && isdigit(from[7]) && isdigit(from[8]) && isdigit(from[9]))){
            cout<<"\nThe format of date is not match.\n";
            return;
        }
        stringstream ss;
        ss << from;
        char temp;
        ss >> fd >> temp >> fm >> temp >> fy;
        cout << "To : ";
        string to = readString();
        if(!(to.size() == 10 && isdigit(to[0]) && isdigit(to[1]) && to[2] == '/' && isdigit(to[3]) && isdigit(to[4]) && to[5] == '/' && isdigit(to[6]) && isdigit(to[7]) && isdigit(to[8]) && isdigit(to[9]))){
            cout<<"\nThe format of date is not match.\n";
            return;
        }
        ss.clear();
        ss << to;
        ss >> td >> temp >> tm >> temp >> ty;
        if (!checkDate (fd, fm, fy, td, tm, ty)){
            cout << "\n'from' is less than or equal to 'to'\n";
            return;
        }
        for (int i = 0; i < list.size (); i++){
            if (!checkDate (fd, fm, fy, list[i].getDay (), list[i].getMonth (), list[i].getYear ())
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
            cout<<"\nThe format of time is not match.\n";
            return;
        }
        stringstream ss;
        ss<<from;
        char temp;
        ss >> fh >> temp >> fm;
        cout << "To : ";
        string to = readString();
        if(!(to.size() == 5 && isdigit(to[0]) && isdigit(to[1]) && to[2] == ':' && isdigit(to[3]) && isdigit(to[4]))){
            cout<<"\nThe format of time is not match.\n";
            return;
        }
        ss.clear();
        ss<<to;
        ss >> th >> temp >> tm;
        if (!checkTime (fh, fm, th, tm)){
            cout << "\n'from' is less than or equal to 'to'\n";
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

void Admin::displaySingleEntry(const vector<Database_handler> &list)const{
    cout<<"\n                                       History                                     \n";
    cout<<"-----------------------------------------------------------------------------------\n";
    if(list.size()==0){
        cout<<"Result Not Found.\n\n";
        return;
    }
    cout<<"Gate\tDate\t\tTime\t      Entry/Exit    Vehicle/Person\tID\n";
    cout<<"-----------------------------------------------------------------------------------\n";
    for(int i=0;i<list.size();i++){
        cout<<list[i].getGateNo()<<"\t"<<list[i].getDay()<<"/"<<list[i].getMonth()<<"/"<<list[i].getYear()<<"\t"<<list[i].getHr()<<":"<<list[i].getMin()<<"\t\t";
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

