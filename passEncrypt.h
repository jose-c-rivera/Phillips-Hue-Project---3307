#include <string>
#ifndef PASSENCRYPT_H
#define PASSENCRYPT_H

/*
 * File: passEncrypt.h
 * Purpose: Contains methods to hash passwords, and compare them to stored
 *          values in a database.
 * Language: C++
*/

using namespace std;

class passEncrypt {

public:

string tempPass;

passEncrypt();
string hashPass(string input_string);
int comparePass(string input_string, string stored_string);
void setTemp(string temp);
string getTemp();

};

#endif
