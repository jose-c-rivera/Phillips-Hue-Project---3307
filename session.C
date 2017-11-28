/**
 * @file    session.C
 * @Author  Jose Rivera <jrivera4@uwo.ca>
 * @date    Novemeber 2017
 * @brief   Class for storing the current user that is logged in
 */

#include <string>

using namespace std;

/**
 * @name: Session_User()
 * @brief: Creates a session object
 * @return: Session object
 */
class Session_User{

   string userEmail;

public:

   void setUserEmail(string input);
 
   string getUserEmail();
};

/**
 * @name: setUserEmail()
 * @brief: Set the username of the current user
 * @param: String to replace current user
 */
void Session_User::setUserEmail(string input){
   userEmail = input;
}

/**
 * @name: getUserEmail()
 * @brief: Return current user string from object
 * @return: String pertaining to current user
 */
string Session_User::getUserEmail(){
   return userEmail;
}
