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

using namespace Wt;

AccountWidget::AccountWidget(WContainerWidget *parent)
        : WContainerWidget(parent){

    addStyleClass("account_container");

    WLineEdit *firstName = new WLineEdit();
    firstName->setPlaceholderText("First Name");
    WPushButton *buttonFirstName = new WPushButton("Change First Name"); 
    addWidget(firstName);
    addWidget(buttonFirstName);
    addWidget(new WText("<p></p>"));
    firstName->setTextSize(20);

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
/*
	WContainerWidget *Info = new WContainerWidget();
	
	Info->addWidget(new WText("Email: Placeholder"));
	Info->addWidget(email);
	Info->addWidget(buttonEmail);

	Info->addWidget(new WText("First Name: Placeholder"));
	Info->addWidget(firstName);
	//Info->addWidget(buttonFirstName);

	Info->addWidget(new WText("Last Name: Placeholder"));
	Info->addWidget(lastName);
	Info->addWidget(buttonLastName);

	Info->addWidget(new WText("Password: Placeholder"));
	Info->addWidget(password);
	Info->addWidget(buttonPassword);
/*
	buttonEmail->clicked().connect(std::bind([=]() {session_database->modifyEmail("Placeholder", email->text().toUTF8());
	}));
	buttonFirstName->clicked().connect(std::bind([=]() {session_database->modifyFirstName("Placeholder", firstName->text().toUTF8());
	}));
	buttonLastName->clicked().connect(std::bind([=]() {session_database->modifyLastName("Placeholder", lastName->text().toUTF8());
	}));
	buttonPassword->clicked().connect(std::bind([=]() {session_database->modifyPassword("Placeholder", password->text().toUTF8());
	}));

	buttonDelete->clicked().connect(std::bind([=]() {session_database->deleteUser("Placeholder");
	})); */
}

