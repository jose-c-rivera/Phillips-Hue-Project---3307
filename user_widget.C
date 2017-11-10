//Displays the account information

#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WContainerWidget>
#include "hueProject.C"


class About : public WApplication{

	public:
		About(const WEnvironment& aboutEnv);	

};
About::About(const WEnvironment& aboutEnv): WApplication(aboutEnv){
	setTitle("About");

	WLineEdit *firstName = new WLineEdit();
	firstName ->setPlaceholderText("Please enter your new First Name");
	WPushButton *buttonFirstName = new WPushButton("Change First Name");

	WLineEdit *email = new WLineEdit();
	email -> setPlaceholderText("Enter your new Email");
	WPushButton *buttonEmail = new WPushButton("Change Email"); 

	WLineEdit *lastName = new WLineEdit();
	lastName -> setPlaceholderText("Please enter your new last name");
	WPushButton *buttonLastName = new WPushButton("Change Last Name");

	WLineEdit *password = new WLineEdit();
	password -> setPlaceholderText("Please enter your new password");
	WPushButton *buttonPassword = new WPushButton("Change Password");

	WPushButton *buttonDelete = new WPushButton("Delete Account");

	WContainerWidget *Info = new WContainerWidget();
	
	Info -> addWidget(new WText("Current Email: Placeholder"));
	Info -> addWidget(email);	
	Info -> addWidget(buttonEmail);

	Info -> addWidget(new WText("Current First Name: Placeholder"));
	Info -> addWidget(firstName);
	Info -> addWidget(buttonFirstName);

	Info -> addWidget(new WText("Current Last Name: Placeholder"));
	Info -> addWidget(lastName);
	Info -> addWidget(buttonLastName);

	Info -> addWidget(new WText("Current Password: Placeholder"));
	Info -> addWidget(password);
	Info -> addWidget(buttonPassword);

	buttonEmail->clicked().connect(std::bind([=]() {session_database->modifyEmail("Placeholder", email->text().toUTF8());
	}));
	buttonFirstName->clicked().connect(std::bind([=]() {session_database->modifyFirstName("Placeholder", firstName->text().toUTF8());
	}));
	buttonLastName->clicked().connect(std::bind([=]() {session_database->modifyLastName("Placeholder", lastName->text().toUTF8());
	}));
	buttonPassword->clicked().connect(std::bind([=]() {session_database->modifyPassword("Placeholder", password->text().toUTF8());
	}));

	buttonDelete->clicked().connect(std::bind([=]() {session_database->deleteUser("Placeholder");
	}));
}

WApplication *aboutApplication(const WEnvironment& aboutEnv)
{
  return new About(aboutEnv);
}

