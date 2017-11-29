/**
 * @file    AccountWidget.C
 * @Author  Jose Rivera <jrivera4@uwo.ca>
 *          Mike Davis 
 * @date    Novemeber 2017
 * @brief   Widget that displays user account details
 */
#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/WText>
#include <Wt/WApplication>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/WMessageBox>
#include <string>
#include "AccountWidget.h"
#include "hueWidget.h"
#include "database.C"

using namespace Wt;

extern string currentUser;

/**
 * @name: AccountWidget()
 * @param: Accepts a WContainerWidget to set as parent of widget
 * @brief: Creates an account widget
 */
AccountWidget::AccountWidget(WContainerWidget *parent)
        : WContainerWidget(parent)
{
    addStyleClass("account_container");
    
    //Creation of database object to insert into sqlite3
    Database* accountPageDB = new Database();

    //Display the user that is currently logged in
    addWidget(new WText("<b>Username: </b>" + currentUser));
    addWidget(new WText("<p></p>"));

    //Display the user's email
    addWidget(new WText("<b>Email: </b>" + accountPageDB->getUserEmail(currentUser)));
    addWidget(new WText("<p></p>"));

    //Display user's first name
    addWidget(new WText("<b>First Name: </b>" + accountPageDB->getUserFirstName(currentUser)));
    addWidget(new WText("<p></p>"));

    //Display user's last name
    addWidget(new WText("<b>Last Name: </b>" + accountPageDB->getUserLastName(currentUser)));
    addWidget(new WText("<p></p>"));

   
    //Line edit to allow user to change first name
    WLineEdit *firstName = new WLineEdit();
    firstName->setPlaceholderText("First Name");
    firstName->setTextSize(20);
    addWidget(firstName);
    WPushButton *buttonFirstName = new WPushButton("Change First Name"); 
    addWidget(buttonFirstName);
    addWidget(new WText("<p></p>"));

    //Line edit to allow user to change last name
    WLineEdit *lastName = new WLineEdit();
    lastName->setPlaceholderText("New Last Name");
    addWidget(lastName);
    WPushButton *buttonLastName = new WPushButton("Change Last Name");
    addWidget(buttonLastName); 
    addWidget(new WText("<p></p>"));
    lastName->setTextSize(20);

    //Line edit to allow user to change email
    WLineEdit *email = new WLineEdit();
    email->setPlaceholderText("New Email");
    WPushButton *buttonEmail = new WPushButton("Change Email");
    addWidget(email);
    addWidget(buttonEmail); 
    addWidget(new WText("<p></p>"));
    email->setTextSize(20);
  
    //Line edit to allow user to change password(stores hash)
    WLineEdit *password = new WLineEdit();
    password->setPlaceholderText("New password");
    WPushButton *buttonPassword = new WPushButton("Change Password");
    addWidget(password);
    addWidget(buttonPassword); 
    addWidget(new WText("<p></p>"));
    password->setTextSize(20);

    //Deletes user account when clicked
    WPushButton *buttonDelete = new WPushButton("Delete Account");
    addWidget(buttonDelete);	

    //Adds all the modification edits to container to manipulate with CSS
    WContainerWidget *modify = new WContainerWidget();
    modify->addWidget(new WText("<h3>Edit Info</h3><p>Use the form below to update your credentials.</p>"));
    modify->addWidget(firstName);
    modify->addWidget(buttonFirstName);
    modify->addWidget(new WText("<p></p>"));
    modify->addWidget(lastName);
    modify->addWidget(buttonLastName);
    modify->addWidget(new WText("<p></p>"));
    modify->addWidget(email);
    modify->addWidget(buttonEmail);
    modify->addWidget(new WText("<p></p>"));
    modify->addWidget(password);
    modify->addWidget(buttonPassword);
    modify->addWidget(new WText("<p></p>"));
    modify->addWidget(buttonDelete);
    addWidget(modify);

/*-----------------------------------HANDLE FIRST NAME BUTTON-----------------------------------*/
	buttonFirstName->clicked().connect(std::bind([=]() {
                cout <<"The first name in field is:"<< firstName->text() << endl;
		accountPageDB->modifyFirstName(currentUser, 
				firstName->text().toUTF8());
	}));
	buttonFirstName->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Your first name has been updated.",
                             StandardButton::Ok);
	}));
/*-----------------------------------HANDLE LAST NAME BUTTON------------------------------------*/
	buttonLastName->clicked().connect(std::bind([=]() {accountPageDB->modifyLastName(currentUser, lastName->text().toUTF8());
	}));
	buttonLastName->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Your last name has been updated.",
                             StandardButton::Ok);
	}));
/*-------------------------------------HANDLE EMAIL BUTTON--------------------------------------*/
	buttonEmail->clicked().connect(std::bind([=]() {
		accountPageDB->modifyEmail(currentUser, 
					   email->text().toUTF8());
	}));
	buttonEmail->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Your email has been updated.",
                             StandardButton::Ok);
	}));
/*-------------------------------------HANDLE PASSWORD BUTTON-----------------------------------*/
	buttonPassword->clicked().connect(std::bind([=]() {accountPageDB->modifyPassword(currentUser, password->text().toUTF8());
	}));
	buttonPassword->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Your password has been updated.",
                             StandardButton::Ok);
	}));
/*--------------------------------HANDLE DELETE ACCOUNT BUTTON----------------------------------*/
	buttonDelete->clicked().connect(std::bind([=]() {accountPageDB->deleteUser(currentUser);
	})); 
	buttonDelete->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "This account has been deleted.",
                             StandardButton::Ok);
	}));
}


