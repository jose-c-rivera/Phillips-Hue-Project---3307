#include <Wt/WAnchor>
#include <Wt/WText>
#include <Wt/WStackedWidget>
#include <Wt/WApplication>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include "hueWidget.h"
#include "AccountWidget.h"
#include "database.C"
#include "passEncrypt.C"

using namespace Wt;

hueWidget::hueWidget(WContainerWidget *parent):
        WContainerWidget(parent),
        myAccount(0)
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
    ///////////////////////////////////

    Database* session_database = new Database();

    //Header container and information
    WContainerWidget *header = new WContainerWidget();
    header->addStyleClass("header");
    header->addWidget(new WText("<h1>Phillips Hue Web Control App</h1>"));

    //Navigation
    WContainerWidget *nav = new WContainerWidget();
    nav->addStyleClass("navi");
    WContainerWidget *nav_main = new WContainerWidget();
    nav_main->addStyleClass("navi_main");
    nav->addWidget(nav_main);
    WContainerWidget *nav_login = new WContainerWidget();
    nav_login->addStyleClass("navi_login");
    nav->addWidget(nav_login);
    
    WAnchor *myAccountAnchor = new WAnchor("/myaccount", "My Account");
    myAccountAnchor->setLink(WLink(WLink::InternalPath, "/myaccount"));
    nav->addWidget(myAccountAnchor);
    WAnchor *myBridges = new WAnchor("/mybridges", "My Bridges");
    myBridges->setLink(WLink(WLink::InternalPath, "/mybridges"));
    nav->addWidget(myBridges);

    //login state
    WText *login_state = new WText("");
    login_state->setText("Not Logged In");
    nav_login->addWidget(login_state);

    //logout button
    WPushButton *logoutButton = new WPushButton();
    logoutButton->setText("Logout");
    logoutButton->setMargin(10, Left);
    nav_login->addWidget(logoutButton);

    //myBridgesAnchor = nav->addWidget(cpp14::make_unique<WAnchor>("/mybridges", "My Account"));

    //content container (includes the body of the page)
    WContainerWidget *content = new WContainerWidget();
    content->addStyleClass("content");
    content->addWidget(new WText("<h2>Welcome to the Philips Hue web control app.</h2>"));
    content->addWidget(new WText("<p>The Philips Hue lighting system lets you easily control your light allowing you to set the perfect ambience for any occasion.</p><p>"
                                         "With our web app, you can add all of your Philips Hue lights and control them from anywhere. To get started, login below. Or,"
                                         "if you don't have an account, please register.</p>"));  // show some text

    WLineEdit *username = new WLineEdit();
    username->setPlaceholderText("Email");
    username->setTextSize(20);

    WLineEdit *password = new WLineEdit();
    password->setPlaceholderText("Password");
    password->setTextSize(20);

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
    regFName->setTextSize(20);

    WLineEdit *regLName = new WLineEdit();
    regLName->setPlaceholderText("Last name");
    regLName->setTextSize(20);

    WLineEdit *regEmail = new WLineEdit();
    regEmail->setPlaceholderText("Email");
    regEmail->setTextSize(20);

    WLineEdit *regPass = new WLineEdit();
    regPass->setPlaceholderText("Password");
    regPass->setTextSize(20);

    WLineEdit *regPassConfirm = new WLineEdit();
    regPassConfirm->setPlaceholderText("Confirm password");
    regPassConfirm->setTextSize(20);

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

    addWidget(header);
    addWidget(nav);


    WApplication::instance()->internalPathChanged().connect(this, &hueWidget::handleInternalPath);

    WPushButton *buttonReg = new WPushButton("Register", regUser);
    buttonReg->setMargin(0, Left);

    buttonReg->clicked().connect(std::bind([=]() {
        session_database->registerUser(regFName->text().toUTF8(),
                                       regLName->text().toUTF8(),
                                       regEmail->text().toUTF8(),
                                       register_insert(regPass));
    }));
    buttonReg->clicked().connect(buttonReg, &WPushButton::disable);
    buttonReg->clicked().connect(std::bind([=]() {
        regUser->hide();
    }));

    mainStack = new WStackedWidget();
    mainStack->setStyleClass("mainstack");
    addWidget(mainStack);

    mainStack->addWidget(content);
    mainStack->setCurrentWidget(content);
}


string hueWidget::register_insert(WLineEdit* passEdit){

    passEncrypt* test = new passEncrypt();
    string pass_temp = passEdit->text().toUTF8();
    string output_String = test->hashPass(pass_temp);
    return output_String;
}

void hueWidget::handleInternalPath(const std::string &internalPath)
{
    if(internalPath == "/myaccount")
        showMyAccount();
    //else if(internalPath == "/myBridges")
        //showMyBridges();
    else
        WApplication::instance()->setInternalPath("/", true);
        //showLogin();
}

void hueWidget::showMyAccount()
{
    if(!myAccount)
        myAccount = new AccountWidget(mainStack);
    mainStack->setCurrentWidget(myAccount);
}
/*
void hueWidget::showLogin(){
    mainStack->setCurrentWidget(content);
}

void hueWidget::showMyBridges(){

}*/
