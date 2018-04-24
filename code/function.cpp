
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#include "function.h"



bool checkFileExistence (const char* txtfile){
    std::ifstream file (txtfile);

    if (file.is_open ()){
        file.close ();
        return true;
    }
    else
        return false;
}
/*
std::string takePassword (){
    std::string password;
    password = readString(true);
    return password;
}*/

int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

void Continue(){
    std::cout<<"\nPress any key to continue...";
    getch();
}

std::string takePassword(){
    std::string password = "";
    while(true){
        char c = getch();
        if(c == '\n' || c == ' ' || c == '\t'){
            std::cout<<'\n';
            if(password.size() > 0)
                return password;
            else
                std::cout<<"\nPassword can't be empty.\n\tTry again : ";
        }
        else if(c == 127){
            if(password.length()!=0){
                password.resize(password.length() - 1);
        //        std::cout<<"\b \b";
            }
        }
        else{
        //    std::cout<<'*';
            password += c;
        }
    }
}

int readInt(const int lower, const int upper){
    char number = 0;
    int size = 0;
    while(true){
        char c = getch();
        if(c == '\n'){
            std::cout<<c;
            if(size == 0){
                std::cout<<"\nInput can't be empty.\n";
            }else if(number <= upper && number >= lower)
                break;
            else
                std::cout<<"\nNumber should lies in Interval ["<<lower<<','<<upper<<"].\n";
            std::cout<<"\tTry again : ";
            number = 0;
            size = 0;
        }else if(isdigit(c)){
            size++;
            std::cout<<c;
            number = number * 10 + c-'0';
        }else if(c == 127 && size > 0){
            size--;
            std::cout << "\b \b";
            number /= 10;
        }
    }
    return number;
}

char readChar(){
    char input;
    bool valid = false;
    while(true){
        char ch = getch();
        if(ch == '\n'){
            std::cout<<ch;
            if(valid)
                return input;
            else{
                std::cout<<"\nInput can't be empty.\n";
                std::cout<<"\tTry again : ";
            }
        }else if(ch == 127){
            if(valid)
                std::cout<<"\b \b";
            valid = false;
        }else if(ch != '\t' && ch != ' '){
            input = ch;
            if(valid)
                std::cout <<"\b"<<ch;
            else
                std::cout<<ch;
            valid = true;
        }
    }
}

std::string readString(bool line){
    std::string input = "";
    while(true){
        char ch = getch();
        if(ch == '\n'){
            std::cout<<ch;
            if(input.size() == 0){
                std::cout<<"\nInput can't be empty.\n";
                std::cout<<"\tTry again : ";
            }
            else{
                return input;
            }
        }else if(ch == '\t' || ch == ' '){
            if(line){
                std::cout << "_";
                input += '_';
            }
        }else if(ch == 127){
            if(input.size() > 0){
                std::cout<<"\b \b";
                input.resize(input.size()-1);
            }
        }else{
            std::cout << ch;
            input += ch;
        }
    }
}

bool selectBy (const std::string option){
    char yes;
    std::cout << "\nSelect by " << option << " [y/n] : ";
    while(true){
        yes = readChar();
        if (yes == 'y' || yes == 'Y')
            return true;
        if(yes == 'n' || yes == 'N')
            return false;
        std::cout<<"\nInvalid\n\tTry again : ";
    }
}

bool checkDate (short fd, short fm, short fy, short td, short tm, short ty){
    if (fy < ty)
        return true;
    if (fy > ty)
        return false;
    if (fm < tm)
        return true;
    if (fm > tm)
        return false;
    if (fd <= td)
        return true;
    return false;
}

bool checkTime (short fh, short fm, short th, short tm){
    if (fh < th)
        return true;
    if (fh > th)
        return false;
    if (fm <= tm)
        return true;
    return false;
}

bool checkMobileNo(std::string mobileNo){
    if(mobileNo == "None")
        return true;
    else if(mobileNo.size() != 10)
        return false;
    else if(mobileNo[0] == '0')
        return false;
    else{
        bool valid = true;
        for(int i = 0;i<mobileNo.size();i++){
            if(isdigit(mobileNo[i]))
                valid = true;
            else
                valid = false;
        }
        return valid;
    }
}

