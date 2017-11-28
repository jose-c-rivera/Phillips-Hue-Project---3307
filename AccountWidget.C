/**
 * @file    AccountWidget.C
 * @Author  Jose Rivera <jrivera4@uwo.ca>
 * @date    Novemeber 2017
 * @brief   Widget that displays user account details
 *
 * 
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

AccountWidget::AccountWidget(WContainerWidget *parent)
        : WContainerWidget(parent)
{
    addStyleClass("account_container");
    Database* accountPageDB = new Database();

    addWidget(new WText("Username: " + currentUser));
    addWidget(new WText("<p></p>"));

    addWidget(new WText("Email: " + accountPageDB->getUserEmail(currentUser)));
    addWidget(new WText("<p></p>"));


    addWidget(new WText("First Name: " + accountPageDB->getUserFirstName(currentUser)));
    addWidget(new WText("<p></p>"));


    addWidget(new WText("Last Name: " + accountPageDB->getUserLastName(currentUser)));
    addWidget(new WText("<p></p>"));

   

    WLineEdit *firstName = new WLineEdit();
    firstName->setPlaceholderText("First Name");
    firstName->setTextSize(20);
    addWidget(firstName);
    WPushButton *buttonFirstName = new WPushButton("Change First Name"); 
    addWidget(buttonFirstName);
    addWidget(new WText("<p></p>"));

    WLineEdit *lastName = new WLineEdit();
    lastName->setPlaceholderText("New Last Name");
    addWidget(lastName);
    WPushButton *buttonLastName = new WPushButton("Change Last Name");
    addWidget(buttonLastName); 
    addWidget(new WText("<p></p>"));
    lastName->setTextSize(20);

    WLineEdit *email = new WLineEdit();
    email->setPlaceholderText("New Email");
    WPushButton *buttonEmail = new WPushButton("Change Email");
    addWidget(email);
    addWidget(buttonEmail); 
    addWidget(new WText("<p></p>"));
    email->setTextSize(20);

    WLineEdit *password = new WLineEdit();
    password->setPlaceholderText("New password");
    WPushButton *buttonPassword = new WPushButton("Change Password");
    addWidget(password);
    addWidget(buttonPassword); 
    addWidget(new WText("<p></p>"));
    password->setTextSize(20);

    WPushButton *buttonDelete = new WPushButton("Delete Account");
    addWidget(buttonDelete);	

    WContainerWidget *modify = new WContainerWidget();
    //modify->addStyleClass("register");
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

/*----------------------------------------------------------------------------------------*/
	buttonFirstName->clicked().connect(std::bind([=]() {
                cout <<"The first name in field is:"<< firstName->text() << endl;
		accountPageDB->modifyFirstName(currentUser, 
				firstName->text().toUTF8());
	}));
	buttonFirstName->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Your first name has been updated.",
                             StandardButton::Ok);
	}));
/*----------------------------------------------------------------------------------------*/
	buttonLastName->clicked().connect(std::bind([=]() {accountPageDB->modifyLastName(currentUser, lastName->text().toUTF8());
	}));
	buttonLastName->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Your last name has been updated.",
                             StandardButton::Ok);
	}));
/*----------------------------------------------------------------------------------------*/
	buttonEmail->clicked().connect(std::bind([=]() {
		accountPageDB->modifyEmail(currentUser, 
					   email->text().toUTF8());
	}));
	buttonEmail->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Your email has been updated.",
                             StandardButton::Ok);
	}));
/*----------------------------------------------------------------------------------------*/
	buttonPassword->clicked().connect(std::bind([=]() {accountPageDB->modifyPassword(currentUser, password->text().toUTF8());
	}));
	buttonPassword->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "Your password has been updated.",
                             StandardButton::Ok);
	}));
/*----------------------------------------------------------------------------------------*/
	buttonDelete->clicked().connect(std::bind([=]() {accountPageDB->deleteUser(currentUser);
	})); 
	buttonDelete->clicked().connect(std::bind([=]() {
              WMessageBox::show("Confirm", "This account has been deleted.",
                             StandardButton::Ok);
	}));
/*
        buttonDelete->clicked().connect(std::bind([=]() {
		hueWidget::logout();
	}));*/
}


