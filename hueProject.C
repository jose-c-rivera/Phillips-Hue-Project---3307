#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WImage>
#include <Wt/WCssDecorationStyle>
#include <Wt/WColor>
#include <string>
#include "userAccount.C"

using namespace Wt;
namespace dbo = Wt::Dbo;


class HueProject : public WApplication
{
public:
  HueProject(const WEnvironment& env);
  
  void registerUser(string first, string last, string email, string password);
  string getUserPassword(string input_email);
  void deleteUser(string user_email);
  void modifyFirstName(string user_email, string new_name);
  void modifyLastName(string user_email, string new_name);
  void modifyEmail(string user_email, string new_email);
  void modifyPassword(string user_email, string pass);

private:
  WLineEdit *nameEdit_;
  WText *greeting_;

  void greet();
  void registerNew();
  
};

HueProject::HueProject(const WEnvironment& env)
  : WApplication(env)
{
 useStyleSheet("css/main.css");
    root()->setStyleClass("main");
    setTitle("Hue Project - Team 9");                               // application title

    //registerUser("Jose", "Rivera", "jrivera4@uwo.ca", "SeCrEt");
    //string line = getUserPassword("jrivera4@uwo.ca");
    //deleteUser("rsmith@uwo.ca");
    //modifyFirstName("jrivera4@uwo.ca", "John");
    //modifyLastName("jrivera4@uwo.ca", "Lazarus");
    //modifyPassword("jrivera4@uwo.ca", "SECRET");
    //modifyEmail("jrivera4@uwo.ca", "lays@fritolay.ca");

    //Header container and information
    WContainerWidget *header = new WContainerWidget();
    header->addStyleClass("header");
    header->addWidget(new WText("<h1>Phillips Hue Web Control App</h1>"));

    //content container (includes the body of the page)
    WContainerWidget *content = new WContainerWidget();
    content->addStyleClass("content");
    content->addWidget(new WText("<h2>Welcome to the Philips Hue web control app.</h2>"));
    content->addWidget(new WText("<p>The Philips Hue lighting system lets you easily control your light allowing you to set the perfect ambience for any occasion.</p><p>"
                                         "With our web app, you can add all of your Philips Hue lights and control them from anywhere. To get started, login below. Or,"
                                         "if you don't have an account, please register.</p>"));  // show some text

    WLineEdit *username = new WLineEdit();
    username->setPlaceholderText("Email");
    username->setWidth(150);

    WLineEdit *password = new WLineEdit();
    password->setPlaceholderText("Password");
    password->setWidth(150);

    WContainerWidget *login = new WContainerWidget();
    login->addStyleClass("login");
    login->addWidget(new WText("<h3>Login</h3><p>Enter your username and password.</p>"));
    login->addWidget(username);
    login->addWidget(new WText("<p></p>"));
    login->addWidget(password);
    login->addWidget(new WText("<p></p>"));
    content->addWidget(login);
    WPushButton *buttonLog = new WPushButton("Log In", login);              
    buttonLog->setMargin(0, Left); 

    WLineEdit *regFName = new WLineEdit();
    regFName->setPlaceholderText("First name");
    regFName->setWidth(150);

    WLineEdit *regLName = new WLineEdit();
    regLName->setPlaceholderText("Last name");
    regLName->setWidth(150);

    WLineEdit *regEmail = new WLineEdit();
    regEmail->setPlaceholderText("Email");
    regEmail->setWidth(150);

    WLineEdit *regPass = new WLineEdit();
    regPass->setPlaceholderText("Password");
    regPass->setWidth(150);

    WLineEdit *regPassConfirm = new WLineEdit();
    regPassConfirm->setPlaceholderText("Confirm password");
    regPassConfirm->setWidth(150);

    WContainerWidget *regUser = new WContainerWidget();
    regUser->addStyleClass("register");
    regUser->addWidget(new WText("<h3>Register</h3><p>Fill in the form below to register.</p>"));
    regUser->addWidget(regFName);
    regUser->addWidget(new WText("<p></p>"));
    regUser->addWidget(regLName);
    regUser->addWidget(new WText("<p></p>"));
    regUser->addWidget(regEmail);
    regUser->addWidget(new WText("<p></p>"));
    regUser->addWidget(regPass);
    regUser->addWidget(new WText("<p></p>"));
    regUser->addWidget(regPassConfirm);
    regUser->addWidget(new WText("<p></p>"));
    content->addWidget(regUser);

    root()->addWidget(header);
    root()->addWidget(content);

    WPushButton *buttonReg = new WPushButton("Register", regUser);              
    buttonReg->setMargin(0, Left); 
}

////////////////////////////////////////DATABASE METHODS//////////////////////////////////////////

//Method to create new user object and add them to userAccounts database
void HueProject::registerUser(string first, string last, string email, string password){

  dbo::backend::Sqlite3 sqlite3("userAccounts.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User_Account>("user");
  /*
   * Will only use this when creating database for very first time
   */
  session.createTables();
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



//Method to query database account by email
string HueProject::getUserPassword(string input_email){
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
void HueProject::deleteUser(string user_email){
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
void HueProject::modifyFirstName(string user_email, string new_name){
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
void HueProject::modifyLastName(string user_email, string new_name){
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
void HueProject::modifyEmail(string user_email, string new_email){
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
void HueProject::modifyPassword(string user_email, string pass){
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
////////////////////////////////////////////////MAIN APP//////////////////////////////////////////

WApplication *createApplication(const WEnvironment& env)
{
  return new HueProject(env);
}

int main(int argc, char **argv)
{
//run();
 return WRun(argc, argv, &createApplication);
}

