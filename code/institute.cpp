#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include "database.h"
#include "security.h"
#include "admin.h"
#include "account.h"
#include "function.h"
#include "institute.h"

using namespace std;

void Institute::start (){
    while (true){
        try{
            login ();
        }
        catch(int){}
        system("clear");
        cout << "\n\nWant to QUIT [y/n] : ";
        char quit;
        quit = readChar();
        if (quit == 'y' || quit == 'Y')
            break;
        else if (quit == 'n' || quit == 'N')
            continue;
        else {
            cout<<"\nAborted.\n\n";
            return;
        }
    }
    cout<<'\n';
}

void Institute::showLogin(){
    unsigned int mseconds  = 200;
    mseconds *= 1000;
    unsigned int dots = 10;
    char cycle[] = {'-','\\','|','/'};
    cout<<"\n\n\tLogging in ";
    for(int i = 0;i<dots;i++){
        cout<<cycle[i%4]<<flush;
        usleep(mseconds);
        cout<<'\b';
    }
}

void Institute::login (){
    system("clear");
    cout << "\t+-------------------+\n";
    cout << "\t| Campus In and Out |\n";
    cout << "\t+-------------------+\n";
    cout << "\n\n";
    string username, password;
    cout << "Enter Username : ";
    username = readString();
    cout << "Enter Password : ";
    password = takePassword ();
    Account_Handler account (username, password);
    UserType user = account.verify ();
    if (user == NOONE){
        cout << "\nInvalid Username or Password.\n";
        cout<<"\nPress any key to continue...";
        getch();
        return;
    }else if (user == SECURITY){
        showLogin();
        cout << "\n\nEnter Current Gate Number : ";
        int gateNo;
        gateNo = readInt(MIN_GATE,MAX_GATE);
        Security security (gateNo);
        security.start ();
    }else if (user == ADMIN){
        showLogin();
        Admin admin;
        admin.start ();
    }else{
        cout << "\nSomething went wrong";	// It will never be print.
    }
    return;
}
