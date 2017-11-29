#include <string>
#include <iostream>
#include <stdlib.h>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
#include <Wt/WButtonGroup>
#include <Wt/WRadioButton>
#include <Wt/WGridLayout>
#include "deleteScheduleWidget.h"

using namespace Wt;

DeleteScheduleWidget::DeleteScheduleWidget(WContainerWidget *parent) 
	: WContainerWidget(parent)
{
	//layout = new Wt::WGridLayout();

	//Http client requests
	client = new Wt::Http::Client(this);
	Wt::Http::Message *msg = new Wt::Http::Message();

	deleteText = new WText("<p>Delete Schedule at ID: </p>");
	//layout->addWidget(deleteText, 0, 0);
	addWidget(deleteText);

	deleteAtID = new WLineEdit();
	deleteAtID->setFocus();
	//layout->addWidget(deleteAtID, 0, 1);
	addWidget(deleteAtID);
	
	WPushButton *deleteButton = new WPushButton("Delete Schedule");
	//layout->addWidget(deleteButton, 0, 2);
	addWidget(deleteButton);

	//setLayout(layout);
	deleteButton->clicked().connect(this,&DeleteScheduleWidget::delSchedule);
}

void DeleteScheduleWidget::delSchedule(){
	std::string strID = (deleteAtID->text()).toUTF8();
	Wt::Http::Message *msg = new Wt::Http::Message;
	client->deleteRequest("http://localhost:8000/api/newdeveloper/schedules/"+strID, *msg);
}
