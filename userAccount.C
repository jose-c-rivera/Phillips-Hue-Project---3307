/*
 * File: userAccount.C
 * Purpose: Class to represent user accounts
 * Language: C++
*/

#include <stdlib.h>
#include <string>
#include "bridge.C"

using namespace std;

class User_Account{

private:
   string first_name = "[undefined]";
   string last_name = "[undefined]";
   string email = "[undefined]";
   string password = "[undefined]";
  //Bridge user_bridges[10];

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

/*
int addBridge(Bridge input_bridge){

   for(int i=0; i<array_size(user_bridges); i++){

      if(user_bridges[i] == NULL){
         user_bridges[i] = input_bridge;
         return 0;
      }
      else continue;   
   }
   return 1; //Case if Bridge Array is full
}
*/

};
