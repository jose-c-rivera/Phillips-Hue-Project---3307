/*
 * File: userAccount.C
 * Purpose: Class to represent user accounts
 * Language: C++
*/

#include <stdlib.h>
#include <string>

using namespace std;

class User_Account{

private:
   string first_name = "[undefined]";
   string last_name = "[undefined]";
   string email = "[undefined]";
   string password = "[undefined]";

public:

string getFirstName(){

   return first_name;

}

void setFirstName(string input_name){

   first_name = input_name;

}

string getLastName(){

   return last_name;

}

void setLastName(string input_name){

   last_name = input_name;

}

string getEmail(){

   return email;

}

void setEmail(string input_email){

   email = input_email;

}

string getPassword(){

   return password;

}

string setPassword(string input_pass){

   password = input_pass;

}

};

