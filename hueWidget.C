/**
 * @file    HueWidget.C
 * @Author  Jose Rivera 
 *          Mike Davis 
 * @date    Novemeber 2017
 * @brief   Widget that displays login and register
 */
#include <Wt/WAnchor>
#include <Wt/WStackedWidget>
#include <Wt/WApplication>
#include <Wt/WLineEdit>
#include <Wt/WMessageBox>
#include "hueWidget.h"
#include "AccountWidget.h"
#include "ManageWidget.h"
#include "LightPage.h"
#include "BridgeEdit.h"
#include "SchedulesWidget.h"
#include "database.C"
#include "session.C"

using namespace Wt;

string currentUser;

hueWidget::hueWidget(WContainerWidget *parent):
    WContainerWidget(parent),
    myAccount(0),
    manage(0),
	content(0),
    nav_main(0),
    logoutButton(0),
    loginState(0),
    lights(0),
    bridgeedit(0),
    schedules(0)
{
    ////////Creation of database/////////
    dbo::backend::Sqlite3 sqlite3("userAccounts.db");
    dbo::Session session;
    session.setConnection(sqlite3);
    session.mapClass<User_Account>("user");
    try{
       session.createTables();
       cout << "Created new table" << endl;
    }catch(...){
       cout << "Using existing table" << endl;
    }

    dbo::Session session_bridge;
    session_bridge.setConnection(sqlite3);
    session_bridge.mapClass<Bridge>("bridgeTable");
    try{
       session_bridge.createTables();
       cout << "Created new table" << endl;
    }catch(...){
       cout << "Using existing table" << endl;
    }

    Database* session_database = new Database();
    ///////////////////////////////////

    //Header container and information
    WContainerWidget *header = new WContainerWidget();
    header->addStyleClass("header");
    header->addWidget(new WText("<h1>Phillips Hue Web Control App</h1>"));

    //Navigation
    nav = new WContainerWidget();
    nav->addStyleClass("navi");
    nav_main = new WContainerWidget();
    nav_main->addStyleClass("navi_main");
    nav->addWidget(nav_main);
    WContainerWidget *nav_login = new WContainerWidget();
    nav_login->addStyleClass("navi_login");
    nav->addWidget(nav_login);
    
    WAnchor *myAccountAnchor = new WAnchor("/myaccount", "My Account");
    myAccountAnchor->setLink(WLink(WLink::InternalPath, "/myaccount"));
    nav_main->addWidget(myAccountAnchor);
    WAnchor *manage = new WAnchor("/manage", "Manage");
    manage->setLink(WLink(WLink::InternalPath, "/manage"));
    nav_main->addWidget(manage);
    WAnchor *myLightsAnchor = new WAnchor("/lights", "Lights");
    myLightsAnchor->setLink(WLink(WLink::InternalPath, "/lights"));
    nav_main->addWidget(myLightsAnchor);
    WAnchor *myBridgeEdit = new WAnchor("/editbridges", "Edit Bridges");
    myBridgeEdit->setLink(WLink(WLink::InternalPath, "/editbridges"));
    nav_main->addWidget(myBridgeEdit);
    WAnchor *myScheduleAnchor = new WAnchor("/schedules", "Schedules");
    myScheduleAnchor->setLink(WLink(WLink::InternalPath, "/schedules"));
    nav_main->addWidget(myScheduleAnchor);

    /*
    WAnchor *myScheduleAnchor = new WAnchor("/schedule", "Schedule");
    myScheduleAnchor->setLink(WLink(WLink::InternalPath, "/schedule"));
    nav_main->addWidget(myScheduleAnchor);
    */

    //login state
    loginState = new WText("");
    loginState->setText("Not Logged In");
    nav_login->addWidget(loginState);

    //logout button
    logoutButton = new WPushButton();
    logoutButton->setText("Logout");
    logoutButton->setMargin(10, Left);
    nav_login->addWidget(logoutButton);
    logoutButton->hide();

    //logout button clicked
    logoutButton->clicked().connect(std::bind([=]() {
        logout();
    }));
    
    nav_main->hide();
    
    //content container (includes the body of the page)
    content = new WContainerWidget();
    content->addStyleClass("content");
    content->addWidget(new WText("<h2>Welcome to the Philips Hue web control app.</h2>"));
    content->addWidget(new WText("<p>The Philips Hue lighting system lets you easily control your light allowing you to set the perfect ambience for any occasion.</p><p>"
                                         "With our web app, you can add all of your Philips Hue lights and control them from anywhere. To get started, login below. Or,"
                                         "if you don't have an account, please register.</p>"));  // show some text

    WLineEdit *username = new WLineEdit();
    username->setPlaceholderText("Username");
    username->setTextSize(20);

    WLineEdit *password = new WLineEdit();
    password->setPlaceholderText("Password");
    password->setEchoMode(password->Password);
    password->setTextSize(20);

    WContainerWidget *login = new WContainerWidget();
    login->addStyleClass("login");
    login->addWidget(new WText("<h3>Login</h3><p>Enter your Username and Password.</p>"));
    login->addWidget(username);
    login->addWidget(new WText("<p></p>"));
    login->addWidget(password);
    login->addWidget(new WText("<p></p>"));
    content->addWidget(login);
    WPushButton *buttonLog = new WPushButton("Log In", login);
    buttonLog->setMargin(0, Left);
    buttonLog->clicked().connect(std::bind([=]() {
        LogIn(session_database,
              username->text().toUTF8(),
              password->text().toUTF8());
    }));

    WLineEdit *regUserName = new WLineEdit();
    regUserName->setPlaceholderText("Username");
    regUserName->setTextSize(20);

    WLineEdit *regFName = new WLineEdit();
    regFName->setPlaceholderText("First name");
    regFName->setTextSize(20);

    WLineEdit *regLName = new WLineEdit();
    regLName->setPlaceholderText("Last name");
    regLName->setTextSize(20);

    WLineEdit *regEmail = new WLineEdit();
    regEmail->setPlaceholderText("Email");
    regEmail->setTextSize(20);

    WLineEdit *regPass = new WLineEdit();
    regPass->setPlaceholderText("Password");
    regPass->setEchoMode(regPass->Password);
    regPass->setTextSize(20);

    WLineEdit *regPassConfirm = new WLineEdit();
    regPassConfirm->setPlaceholderText("Confirm password");
    regPassConfirm->setEchoMode(regPassConfirm->Password);
    regPassConfirm->setTextSize(20);

    WContainerWidget *regUser = new WContainerWidget();
    regUser->addStyleClass("register");
    regUser->addWidget(new WText("<h3>Register</h3><p>Fill in the form below to register.</p>"));
    regUser->addWidget(regUserName);
    regUser->addWidget(new WText("<p></p>"));
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

    addWidget(header);
    addWidget(nav);
    addWidget(content);

    WApplication::instance()->internalPathChanged().connect(this, &hueWidget::handleInternalPath);

    WPushButton *buttonReg = new WPushButton("Register", regUser);
    buttonReg->setMargin(0, Left);

    buttonReg->clicked().connect(std::bind([=]() {
        session_database->registerUser(regUserName->text().toUTF8(),
				       regFName->text().toUTF8(),
                                       regLName->text().toUTF8(),
                                       regEmail->text().toUTF8(),
                                       register_hash(regPass),
				       register_hash(regPassConfirm));
    }));
    buttonReg->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Thank you for creating an account! Please Log In using your new credentials.",
                             StandardButton::Ok);
    }));
    buttonReg->clicked().connect(buttonReg, &WPushButton::disable);

    mainStack = new WStackedWidget();
    mainStack->setStyleClass("mainstack");
    addWidget(mainStack);

}


string hueWidget::register_hash(WLineEdit* passEdit){

    passEncrypt* test = new passEncrypt();
    string pass_temp = passEdit->text().toUTF8();
    string output_String = test->hashPass(pass_temp);
    return output_String;
}

void hueWidget::LogIn(Database* db, string userName, string password){
    passEncrypt* test = new passEncrypt();
    string tempHash = test->hashPass(password);
  
   if(tempHash.compare(db->getUserPassword(userName)) == 0){
      currentUser = userName;
      WApplication::instance()->setInternalPath("/myaccount", true);
      //showMyAccount();
      //handleInternalPath("/myaccount");
      cout << "Log In: Succesful!" << endl;
      cout << "Current User is: " << userName << endl; 
      showNav();
      WString loggedUser = "Logged in as: " + userName;
      loginState->setText(loggedUser);
      content->hide();
   }
   else
      cout << "Log In: Failed." << endl;
}

void hueWidget::handleInternalPath(const std::string &internalPath)
{
    cout << "\n\nINTERNAL PATH CHANGE\n\n";
    if(internalPath == "/myaccount"){
        cout << "\n\nCalling show my account\n\n";
        showMyAccount();
    }
    else if(internalPath == "/manage"){
        showManage();
    }
    else if(internalPath == "/lights"){
        showLights();
    }
    else if(internalPath == "/schedules"){
        showSchedules();
    }
    else if(internalPath == "/editbridges"){
        showBridgeEdit();
    }
    else{
        WApplication::instance()->setInternalPath("/", true);
        showLogin();
    }
}

void hueWidget::showMyAccount()
{
    if(!myAccount){
        myAccount = new AccountWidget(mainStack);
    }
    mainStack->setCurrentWidget(myAccount);
    mainStack->show();
    //myAccount->update();
}

void hueWidget::showManage(){
    std::string test = "test";
    if(!manage)
        manage = new ManageWidget(test, mainStack);
    mainStack->setCurrentWidget(manage);
}

void hueWidget::showLogin(){
    content->show();
    mainStack->hide();
}

void hueWidget::showNav(){
    nav_main->show();
    logoutButton->show();
}

void hueWidget::showLights(){
    if(!lights){
        lights = new LightPage(mainStack);
    }
    mainStack->setCurrentWidget(lights);
}

void hueWidget::showSchedules(){
    if(!schedules){
        schedules = new SchedulesWidget(mainStack);
    }
    mainStack->setCurrentWidget(schedules);
}

void hueWidget::showBridgeEdit(){
    cout << "\n\nShowing Bridge Edit";
    if(!bridgeedit){
        bridgeedit = new BridgeEdit(mainStack);
    }
    mainStack->setCurrentWidget(bridgeedit);
}

void hueWidget::logout(){
    //mainStack->removeWidget(myAccount);
    nav_main->hide();
    logoutButton->hide();
    content->show();
    loginState->setText("Not Logged In");
    WApplication::instance()->setInternalPath("/", true);
    WApplication::instance()->redirect("http://localhost:8080");
}
