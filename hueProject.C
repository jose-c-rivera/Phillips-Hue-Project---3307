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
#include "database.C"

using namespace Wt;


class HueProject : public WApplication
{
public:
  HueProject(const WEnvironment& env);

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
    setTitle("Hue Project - Team 9");

    Database *session_database = new Database();

    session_database->registerUser("Jose", "Rivera", "jrivera4@uwo.ca", "SeCrEt");

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

