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

using namespace std;
namespace dbo = Wt::Dbo;

class Database{

public:

void registerUser(string first, string last, string email, string password, string passwordConfirm){

  if(password.compare(passwordConfirm) == 0){
     cout << "Passwords match. User was registered" << endl;
     dbo::backend::Sqlite3 sqlite3("userAccounts.db");
     dbo::Session session;
     session.setConnection(sqlite3);
     session.mapClass<User_Account>("user");
     {
       dbo::Transaction transaction(session);
       User_Account *user = new User_Account();
       user->setFirstName(first);
       user->setLastName(last);
       user->setEmail(email);
       user->setPassword(password);
       dbo::ptr<User_Account> userPtr = session.add(user);
     }
  }
  else cout << "Passwords dont match! User was not registered" << endl;
}



//Method to query database account by email
string getUserPassword(string input_email){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> user_query = session.find<User_Account>().where("email = ?").bind(input_email);
    return user_query->password;
  }
}

//Method to erase a user from the database
void deleteUser(string user_email){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> trash = session.find<User_Account>().where("email = ?").bind(user_email);
    if (trash)
      trash.remove();
  }
}

//Method to modify user's first name
void modifyFirstName(string user_email, string new_name){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> mod = session.find<User_Account>().where("email = ?").bind(user_email);
    mod.modify()->first_name = new_name;
 }
}
//Method to modify user's last name
void modifyLastName(string user_email, string new_name){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> mod = session.find<User_Account>().where("email = ?").bind(user_email);
    mod.modify()->last_name = new_name;
 }
}

//Method to modify user's email
void modifyEmail(string user_email, string new_email){
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> mod = session.find<User_Account>().where("email = ?").bind(user_email);
    mod.modify()->email = new_email;
 }
}

//Method to modify user's password
void modifyPassword(string user_email, string pass){
  //Should call hash function before saving
  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
 {
    dbo::Transaction transaction(session);
    dbo::ptr<User_Account> mod = session.find<User_Account>().where("email = ?").bind(user_email);
    mod.modify()->password = pass;
 }
}

};
