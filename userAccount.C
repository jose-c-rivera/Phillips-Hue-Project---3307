/**
 * @file    userAccount.C
 * @Author  Jose Rivera <jrivera4@uwo.ca>
 * @date    Novemeber 2017
 * @brief   Class for user account objects
 */
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>
#include "bridge.C"

using namespace std;
namespace dbo = Wt::Dbo;

/**
 * @name: User Account Constructor
 * @brief: Creates a user account object
 * @return: Account Object
 */
class User_Account{

public:
   string user_name;
   string first_name;
   string last_name;
   string email;
   string password;

/*
 * Template to map fields of object to database table
 */
template<class Action>
   void persist(Action& a)
{
      dbo::field(a, user_name, "user_name");
      dbo::field(a, first_name, "first_name");
      dbo::field(a, last_name, "last_name");
      dbo::field(a, email, "email");
      dbo::field(a, password, "password");
  }

/**
 * @name: getUserName()
 * @brief: return the username for the user
 * @return: string 
 */
string getUserName(){

   return user_name;

}

/**
 * @name: setUserName(string input_name)
 * @param: The parmater will be the new userName
 * @brief: sets the new user name
 */
void setUserName(string text){

   user_name = text;

}

/**
 * @name: getFirstName()
 * @brief: return the first name for the user
 * @return: string 
 */
string getFirstName(){

   return first_name;

}

/**
 * @name: setFirstName(string input_name)
 * @param: The paramater will be the new first name
 * @brief: sets the new user first name
 */
void setFirstName(string input_name){

   first_name = input_name;

}

/**
 * @name: getLastName()
 * @brief: return the last name for the user
 * @return: string 
 */
string getLastName(){

   return last_name;

}

/**
 * @name: setLastName(string input_name)
 * @param: The paramater will be the new last name
 * @brief: sets the new last name for the user
 */
void setLastName(string input_name){

   last_name = input_name;

}

/**
 * @name: getEmail()
 * @brief: return the email for the user
 * @return: string 
 */
string getEmail() const{

   return email;

}

/**
 * @name: setEmail(string input_email)
 * @param: The parameter will be the new email
 * @brief: sets the new email for the user
 */
void setEmail(string input_email){

   email = input_email;

}

/**
 * @name: getPassword()
 * @brief: return the password(hash) for the user
 * @return: string 
 */
string getPassword(){

   return password;

}

/**
 * @name: setPassword(string input_name)
 * @param: The parameter will be the new password
 * @brief: sets the new user password
 */
void setPassword(string input_pass){

   password = input_pass;

}

};
