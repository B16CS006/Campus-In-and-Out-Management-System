#ifndef FUNCTION_H
#define FUNCTION_H

#define MAX_GATE 10
#define MIN_GATE 1

bool checkFileExistence (const char*);

int getch();

void Continue();

std::string takePassword ();

int readInt(const int lower = 0, const int upper = 100);

char readChar();

std::string readString(bool line = false);

bool selectBy (const std::string);

bool checkDate (short, short, short, short, short, short);

bool checkTime (short, short, short, short);

bool checkMobileNo(std::string);

#endif
