/*
 * File: database.C
 * Purpose: Contains methods to insert, remove and modify entries in a database
 * Language: C++
*/

#include <math.h>
#include <stdlib.h>
#include <string>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include "userAccount.C"
#include "passEncrypt.C"

using namespace std;
namespace dbo = Wt::Dbo;

typedef Wt::Dbo::collection< Wt::Dbo::ptr<User_Account> > Users;

class Database{

public:

void registerUser(string userName, string first, string last, string email, string password, string passwordConfirm){

  if(password.compare(passwordConfirm) == 0){
     cout << "Passwords match. User was registered" << endl;
     dbo::backend::Sqlite3 sqlite3("userAccounts.db");
     dbo::Session session;
     session.setConnection(sqlite3);
     session.mapClass<User_Account>("user");
     {
       dbo::Transaction transaction(session);
       User_Account *user = new User_Account();
       user->setUserName(userName);
       user->setFirstName(first);
       user->setLastName(last);
       user->setEmail(email);
       user->setPassword(password);
       dbo::ptr<User_Account> userPtr = session.add(user);
     }
	//hueWidget::handleInternalPath("/myaccount");
  }
  else cout << "Passwords dont match! User was not registered" << endl;
}

//Method to get a user's first name using their username
string getUserFirstName(string input_user){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> user_query = session.find<User_Account>().where("user_name = ?").bind(input_user);
    return user_query->first_name;
  }
}

//Method to get a user's last name using their email
string getUserLastName(string input_user){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> user_query = session.find<User_Account>().where("user_name = ?").bind(input_user);
    return user_query->last_name;
  }
}

//Method to get a user's first name using their username
string getUserEmail(string input_user){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> user_query = session.find<User_Account>().where("user_name = ?").bind(input_user);
    return user_query->email;
  }
}

//Method to query database account by email to retrieve password
string getUserPassword(string input_user){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> user_query = session.find<User_Account>().where("user_name = ?").bind(input_user);
    return user_query->password;
  }
}

//Method to erase a user from the database
void deleteUser(string user_name){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> trash = session.find<User_Account>().where("user_name = ?").bind(user_name);
    if (trash)
      trash.remove();
  }
}

//Method to modify user's first name
void modifyFirstName(string user_name, string new_name){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> mod = session.find<User_Account>().where("user_name = ?").bind(user_name);
    cout << "new name is: " << new_name << endl;
    mod.modify()->first_name = new_name;
 }
}
//Method to modify user's last name
void modifyLastName(string user_name, string new_name){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> mod = session.find<User_Account>().where("user_name = ?").bind(user_name);
    mod.modify()->last_name = new_name;
 }
}

//Method to modify user's email
void modifyEmail(string user_name, string new_email){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> mod = session.find<User_Account>().where("user_name = ?").bind(user_name);
    mod.modify()->email = new_email;
 }
}

//Method to modify user's password
void modifyPassword(string user_name, string input_pass){
  //Should call hash function before saving
  passEncrypt* temp = new passEncrypt();
  string hashed_pass = temp->hashPass(input_pass);
 
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> mod = session.find<User_Account>().where("user_name = ?").bind(user_name);
    mod.modify()->password = hashed_pass;
 }
}

std::vector<User_Account> userList(){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
  {
    dbo::Transaction transaction(session);

    Users allusers = session.find<User_Account>().where("email = ?").bind("email");
    std::vector<User_Account> result;
    for(Users::const_iterator i = allusers.begin(); i != allusers.end(); i++){
      dbo::ptr<User_Account> user = *i;
      result.push_back(*user);

      string test = user->getEmail();
      cout << test;
    }

    return result;
  }

}

};
