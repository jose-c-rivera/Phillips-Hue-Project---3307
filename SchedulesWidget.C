/*
 * File: SchedulesWidget.C
 * Author: Mike Davis, Allan Rashad Khan 
 * 
 */
#include <string>
#include <iostream>
#include <stdlib.h>
#include <Wt/WApplication>
#include <Wt/Http/Message>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
#include <Wt/WButtonGroup>
#include <Wt/WGridLayout>
#include "deleteScheduleWidget.h"
#include "SchedulesEdit.h"
#include "SchedulesWidget.h"

using namespace std;
using namespace Wt;

//extern currentUser;

SchedulesWidget::SchedulesWidget(WContainerWidget *parent)
	: WContainerWidget(parent),
	deleteSchedule(0),
	editSchedule(0)
{

	WGridLayout *layout = new WGridLayout();

	//CSS
	addStyleClass("schedules");

	client = new Http::Client(this);
	Wt::Http::Message *msg = new Wt::Http::Message();

	WText *groupsMessage = new WText("Groups or Lights?: ");
	layout->addWidget(groupsMessage, 0,0);

	WRadioButton *buttonA = new WRadioButton("Groups");
	buttonA->setMargin(5,Left);
	group->addButton(buttonA, 0);
	layout->addWidget(buttonA, 0, 1);		

	buttonA = new WRadioButton("Lights");
	group->addButton(buttonA, 1);
	group->setCheckedButton(group->button(0));
	layout->addWidget(buttonA, 0, 2);		//Potential error same grid loc

	IDtext = new WText("enter group or light ID*:");
	layout->addWidget(IDtext, 1, 0);	
	IDNum = new WLineEdit();
	IDNum->setFocus();
	layout->addWidget(IDNum, 1, 1);

	WText *textname = new WText("enter a name for the schedule:");
	layout->addWidget(textname, 2, 0);
	schedName = new WLineEdit();
	schedName->setFocus();
	layout->addWidget(schedName, 2, 1);

	WText *textdesc = new WText("enter a description for the schedule: ");
	layout->addWidget(textdesc, 3, 0);
	schedDesc = new WLineEdit();
	schedDesc->setFocus();
	layout->addWidget(schedDesc, 3, 1);

	WText *textdate = new WText("Date for event YYYY-MM-DD*: ");
	layout->addWidget(textdate, 4,0);
	date = new WLineEdit();
	date->setFocus();
	layout->addWidget(date, 4,1);
	//append these two with T
	WText *texttime = new WText("Time for event hh-mm-ss [24hr clock]*: ");
	layout->addWidget(texttime, 5,0);
	time = new WLineEdit();
	time->setFocus();
	layout->addWidget(time, 5,1);

	WText *textenabled = new WText("Do you want schedule enabled or disabled:");
	layout->addWidget(textenabled, 6,0);
	

	buttonA = new WRadioButton("enabled");
	buttonA->setMargin(5,Left);
	groupB->addButton(buttonA);
	layout->addWidget(buttonA, 6,1);

	buttonA = new WRadioButton("disabled");
	groupB->addButton(buttonA);
	groupB->setCheckedButton(groupB->button(0));
	layout->addWidget(buttonA, 6,2);

	WText *textdelete = new WText("Do you want schedule to autodelete?:");
	layout->addWidget(textdelete, 7, 0);
	buttonA = new WRadioButton("Yes");
	buttonA->setMargin(5,Left);
	groupC->addButton(buttonA);
	layout->addWidget(buttonA, 7, 1);

	buttonA = new WRadioButton("No");
	groupC->addButton(buttonA);
	groupC->setCheckedButton(groupC->button(0));
	layout->addWidget(buttonA, 7, 2);

	WText *texton = new WText("Turn lights:");
	layout->addWidget(texton, 8,0);

	buttonA = new WRadioButton("On");
	buttonA->setMargin(5,Left);
	groupD->addButton(buttonA);
	layout->addWidget(buttonA, 8,1);

	buttonA = new WRadioButton("Off");
	groupD->addButton(buttonA);
	groupD->setCheckedButton(groupD->button(0));
	layout->addWidget(buttonA, 8,2);

	briSlider->setMinimum(1);
	briSlider->setMaximum(254);
	briSlider->setValue(127);
	briSlider->resize(50,200);

	hueSlider->setMinimum(0);
	hueSlider->setMaximum(65535);
	hueSlider->setValue(32767);
	hueSlider->resize(50,200);
	
	satSlider->setMinimum(0);
	satSlider->setMaximum(254);
	satSlider->setValue(127);
	satSlider->resize(50,200);	

	WText *briSliderLabel = new WText("Light brightness:");
	WText *hueSliderLabel = new WText("Light Hue:");
	WText *satSliderLabel = new WText("Light brightness:");
	layout->addWidget(briSliderLabel, 9, 0);
	layout->addWidget(hueSliderLabel, 9, 1);
	layout->addWidget(satSliderLabel, 9, 2);

	layout->addWidget(briSlider, 10, 0);
	layout->addWidget(hueSlider, 10, 1);
	layout->addWidget(satSlider, 10, 2);


	WPushButton *finalButton = new WPushButton("Create Schedule", this);
	layout->addWidget(finalButton, 11,0);
	
	finalButton->clicked().connect(this,&SchedulesWidget::schedule_SET);

	editSchedule = new SchedulesEdit(this);
	layout->addWidget(editSchedule, 12, 0);

	deleteSchedule = new DeleteScheduleWidget(this);
	layout->addWidget(deleteSchedule, 13, 0);
	setLayout(layout);

}

void SchedulesWidget::schedule_SET(){
	bool groupFlag = true;
	bool nameFlag = true;
	bool descFlag = true;
	string status = "\"status\": \"enabled\"";
	string autoDel = "true";
	string lightOn = "true";
	string totalPUT;

	if (group->checkedId() == 1)
		 groupFlag = false;
	if (groupB->checkedId()== 1)				//Status isn't supported in emulator
		status = "\"status\": \"disabled\"";
	if (groupC->checkedId()== 1)				//Emulator always auto deletes after execution
		autoDel = "false";
	if (groupD->checkedId()== 1)
		lightOn = "false";
	string strID = (IDNum->text()).toUTF8();
	
	if ((schedName->text()).toUTF8() == "")
		nameFlag = false;
	if ((schedDesc->text()).toUTF8() == "")
		descFlag = false;
	
	string strDate = (date->text()).toUTF8();
	string strTime = (time->text()).toUTF8();
	string DateTime = strDate+"T"+strTime;

	string strBri = (briSlider->valueText()).toUTF8();
	string strHue = (hueSlider->valueText()).toUTF8();
	string strSat = (satSlider->valueText()).toUTF8();

	Http::Message *sched_msg = new Http::Message();
	
	if (groupFlag==1){
		//CHANGE ADDRESS
		string addrPut = "\"address\":\"/api/newdeveloper/groups/"+strID+"/action\"";
		string methodPUT = "\"method\": \"PUT\"";
		
		string schedBody = "\"body\":{\"on\": "+lightOn+", \"bri\":"+strBri+", \"hue\":"+strHue+", \"sat\":"+strSat+"}";
		totalPUT = addrPut+","+methodPUT+","+schedBody;	
		
	}
	else if(groupFlag==0){
		//CHANGE ADDRESS
		string addrPut = "\"address\":\"/api/newdeveloper/lights/"+strID+"/state\"";
		string methodPUT = "\"method\": \"PUT\"";
		string schedBody = "\"body\":{\"on\": "+lightOn+", \"bri\":"+strBri+", \"hue\":"+strHue+", \"sat\":"+strSat+"}";
		totalPUT = addrPut+","+methodPUT+","+schedBody;
		
	}
		
	if (nameFlag == false && descFlag == false)
			sched_msg->addBodyText("{\"command\": {"+totalPUT+"}, \"time\":\""+DateTime+"\", "+status+", \"autodelete\":"+autoDel+"}");
	if (nameFlag == false && descFlag == true)
			sched_msg->addBodyText("{\"description\": \""+(schedDesc->text()).toUTF8()+"\", \"command\": {"+totalPUT+"}, \"time\":\""+DateTime+"\", "+status+", \"autodelete\":"+autoDel+"}");
	if (nameFlag == true && descFlag == false)
			sched_msg->addBodyText("{\"name\": "+(schedName->text()).toUTF8()+", \"command\": {"+totalPUT+"}, \"time\":\""+DateTime+"\", "+status+", \"autodelete\":"+autoDel+"}");
	if (nameFlag == true && descFlag == true)
			sched_msg->addBodyText("{\"name\": "+(schedName->text()).toUTF8()+", \"description\": \""+(schedDesc->text()).toUTF8()+"\", \"command\": {"+totalPUT+"}, \"time\":\""+DateTime+"\", "+status+", \"autodelete\":"+autoDel+"}");

	if (client->post("http://localhost:8000/api/newdeveloper/schedules", *sched_msg)) {
		cout << "POST was successful" << endl;
	}
}
