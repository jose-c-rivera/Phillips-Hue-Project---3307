//Displays the account information

#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
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
    addWidget(firstName);
    firstName->setTextSize(20);
    WPushButton *buttonFirstName = new WPushButton("Change First Name"); 
    addWidget(buttonFirstName);
    addWidget(new WText("<p></p>"));

    WLineEdit *email = new WLineEdit();
    email->setPlaceholderText("New Email");
    WPushButton *buttonEmail = new WPushButton("Change Email");
    addWidget(email);
    addWidget(buttonEmail); 
    addWidget(new WText("<p></p>"));
    email->setTextSize(20);

    WLineEdit *lastName = new WLineEdit();
    lastName->setPlaceholderText("New Last Name");
    addWidget(lastName);
    WPushButton *buttonLastName = new WPushButton("Change Last Name");
    addWidget(buttonLastName); 
    addWidget(new WText("<p></p>"));
    lastName->setTextSize(20);

    WLineEdit *password = new WLineEdit();
    password->setPlaceholderText("New password");
    WPushButton *buttonPassword = new WPushButton("Change Password");
    addWidget(password);
    addWidget(buttonPassword); 
    addWidget(new WText("<p></p>"));
    password->setTextSize(20);

    WPushButton *buttonDelete = new WPushButton("Delete Account");
    addWidget(buttonDelete);	

	buttonFirstName->clicked().connect(std::bind([=]() {
		accountPageDB->modifyFirstName(currentUser, 
				//firstName->text().toUTF8()
				"Luke");
	}));

	buttonEmail->clicked().connect(std::bind([=]() {
		accountPageDB->modifyEmail(currentUser, 
					   email->text().toUTF8());
	}));

	buttonLastName->clicked().connect(std::bind([=]() {accountPageDB->modifyLastName(currentUser, //lastName->text().toUTF8()
"Skywalker");
	}));
	buttonPassword->clicked().connect(std::bind([=]() {accountPageDB->modifyPassword(currentUser, password->text().toUTF8());
	}));

	buttonDelete->clicked().connect(std::bind([=]() {accountPageDB->deleteUser(currentUser);
	})); 
}


