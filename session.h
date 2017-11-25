#include <string>

using namespace std;

class Session_User{

   string userEmail;

public:

   void setUserEmail(string input);
 
   string getUserEmail();
};

void Session_User::setUserEmail(string input){
   userEmail = input;
}

string Session_User::getUserEmail(){
   return userEmail;
}
