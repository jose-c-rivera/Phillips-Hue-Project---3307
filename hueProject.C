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
#include <Wt/WTemplate>
#include <Wt/WColor>
#include <Wt/WString>
#include <string>
#include "database.C"

using namespace Wt;


class HueProject : public WApplication
{
public:
  Database* session_database = new Database();
  HueProject(const WEnvironment& env);

private:
/*
    WAnchor		  *backToGameAnchor_;
    WContainerWidget      *links_;
    WStackedWidget	  *mainStack_;
    MainWidget	          *main_;
    UserProfileWidget     *user_;
    BridgeWidget	  *bridge_;

    Session session_;
*/
  
};

HueProject::HueProject(const WEnvironment& env)
  : WApplication(env)
{
 useStyleSheet("css/main.css");
    root()->setStyleClass("main");
    setTitle("Hue Project - Team 9");

    //session_database->registerUser("Jose", "Rivera", "jrivera4@uwo.ca", "SeCrEt");

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
	WString field1 = regFName->text();
	WString field2 = regLName->text();
	WString field3 = regEmail->text();
	WString field4 = regPass->text();

    root()->addWidget(header);
    root()->addWidget(content);

    WPushButton *buttonReg = new WPushButton("Register", regUser);              
    buttonReg->setMargin(0, Left); 
    buttonReg->clicked().connect(std::bind([=]() { 
         session_database->registerUser(regFName->text().toUTF8(),
					regLName->text().toUTF8(),
					regEmail->text().toUTF8(),
					regPass->text().toUTF8());
   }));
   buttonReg->clicked().connect(buttonReg, &WPushButton::disable);
   buttonReg->clicked().connect(std::bind([=]() { 
         regUser->hide();
   }));

}
/*
void HueProject::handleInternalPath(const std::string &internalPath)
{
    if(internalPath == "/Main")
	showMain();
    else if(internalPath == "/User")
	showUserProfile();
    else if(internalPath == "/Bridge")
	showBridgeEdit();
    else
	WApplication::instance()->setInternalPath("/Main", true);
}

void HueProject::showMain()
{
    if(!main_)
      main_ = mainStack_->addWidget(cpp14::make_unique<MainWidget>(&session_));
    
    mainStack_->setCurrentWidget(main_);
    main_->update();
}

void HueProject::showUserProfile()
{
    if(!user_)
      user_ = mainStack_->addWidget(cpp14::make_unique<UserProfileWidget>(&session_));
    
    mainStack_->setCurrentWidget(user_);
    user_->update();
}

void HueProject::showBridgeEdit()
{
    if(!bridge_)
      bridge_ = mainStack_->addWidget(cpp14::make_unique<BridgeWidget>(&session_));
    
    mainStack_->setCurrentWidget(bridge_);
    bridge_->update();
}
*/
////////////////////////////////////////////////MAIN APP//////////////////////////////////////////

WApplication *createApplication(const WEnvironment& env)
{
  return new HueProject(env);
}

int main(int argc, char **argv)
{
 return WRun(argc, argv, &createApplication);
}

