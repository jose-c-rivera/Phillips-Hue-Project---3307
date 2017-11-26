/*
 * File: userAccount.C
 * Purpose: Class to represent user accounts
 * Language: C++
*/

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>
//#include "bridge.C"
//#include "passEncrypt.h"

using namespace std;
namespace dbo = Wt::Dbo;

class User_Account{

public:
   string first_name;
   string last_name;
   string email;
   string password;

template<class Action>
   void persist(Action& a)
{
      dbo::field(a, first_name, "first_name");
      dbo::field(a, last_name, "last_name");
      dbo::field(a, email, "email");
      dbo::field(a, password, "password");
  }




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

void setPassword(string input_pass){

   password = input_pass;

}

};
