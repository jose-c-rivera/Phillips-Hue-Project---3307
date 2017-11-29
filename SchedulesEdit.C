/**
 * @file SchedulesEdit.C
 * @Authors Allan Khan, Mike Davis 
 * @date November 2017
 * @brief Widget for changing an already existing schedule
 */

#include <Wt/WGridLayout>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <Wt/WApplication>
#include <Wt/Http/Message>
#include <Wt/Http/Request>
#include <Wt/Http/Response>
#include "SchedulesEdit.h"

using namespace std;
using namespace Wt;
extern string currentUser;

/**
 * @name ScheduleEdit
 * @param Accepts a WContainerWidget to set as parent of widget
 * @brief Edits an existing schedule's attributes 
 */
SchedulesEdit::SchedulesEdit(WContainerWidget *parent) 
	: WContainerWidget()
{
	WGridLayout *layout = new WGridLayout();

	//CSS
	addStyleClass("schedule Update");

	//Client to make requests to
	client = new Http::Client(this);

	//Displays text box for user to input an ID number
	IDtext = new WText("enter schedule ID to edit*:");
	layout->addWidget(IDtext, 0, 0);	
	IDNum = new WLineEdit();
	IDNum->setFocus();
	layout->addWidget(IDNum, 0, 1);

	//Displays a text box for user to input name
	WText *textname = new WText("enter a new name for the schedule*:");
	layout->addWidget(textname, 1, 0);
	schedName = new WLineEdit();
	schedName->setFocus();
	layout->addWidget(schedName, 1, 1);

	//Displays a text box for user 
	WText *textdesc = new WText("enter a new description for the schedule*: ");
	layout->addWidget(textdesc, 2, 0);
	schedDesc = new WLineEdit();
	schedDesc->setFocus();
	layout->addWidget(schedDesc, 2, 1);

	WText *textdate = new WText("Date for event YYYY-MM-DD*: ");
	layout->addWidget(textdate, 3,0);
	date = new WLineEdit();
	date->setFocus();
	layout->addWidget(date, 3,1);
	//append these two with T
	WText *texttime = new WText("Time for event hh-mm-ss [24hr clock]*: ");
	layout->addWidget(texttime, 4,0);
	time = new WLineEdit();
	time->setFocus();
	layout->addWidget(time, 4,1);
	
	//Allow the user to turn lights on or off
	WText *texton = new WText("Turn lights:");
	layout->addWidget(texton, 5,0);

	buttonA = new WRadioButton("On");
	buttonA->setMargin(5,Left);
	group->addButton(buttonA);
	layout->addWidget(buttonA, 5,1);

	buttonA = new WRadioButton("Off");
	group->addButton(buttonA);
	group->setCheckedButton(group->button(0));
	layout->addWidget(buttonA, 5,2);

	WText *textreq = new WText("* means required");
	layout->addWidget(textreq, 6,0);

	//Show sliders to change light attributes
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
	layout->addWidget(briSliderLabel, 7, 0);
	layout->addWidget(hueSliderLabel, 7, 1);
	layout->addWidget(satSliderLabel, 7, 2);

	layout->addWidget(briSlider, 8, 0);
	layout->addWidget(hueSlider, 8, 1);
	layout->addWidget(satSlider, 8, 2);

	//Final button push to make request
	WPushButton *finalButton = new WPushButton("Edit Schedule", this);
	layout->addWidget(finalButton, 9,0);

	//Set layout
	setLayout(layout);

	finalButton->clicked().connect(this,&SchedulesEdit::setSchedule);
}

/**
 * @Name setSchedule
 * @param
 * @brief  Makes the call to the emulator to change schedule values
 */
void SchedulesEdit::setSchedule(){
	//Converting attributes to strings
	string strID = (IDNum->text()).toUTF8();
	string strName = (schedName->text()).toUTF8();
	string strDescription = (schedDesc->text()).toUTF8();
	string strDate = (date->text()).toUTF8();
	string strTime = (time->text()).toUTF8();
	string DateTime = strDate+"T"+strTime;
	string lightOn = "true";
	string strBri = (briSlider->valueText()).toUTF8();
	string strHue = (hueSlider->valueText()).toUTF8();
	string strSat = (satSlider->valueText()).toUTF8();
	
	if (group->checkedId()==1){
		lightOn = "false";
	}

	//Compose the body to send
	Http::Message *schedEdit_msg = new Http::Message();
	string editMSG = "\"body\":{\"on\": "+lightOn+", \"bri\":"+strBri+", \"hue\":"+strHue+", \"sat\":"+strSat+"}";
	schedEdit_msg->addBodyText("{\"name\": \""+strName+"\", \"description\": \""+strDescription+"\", \"command\": {"+editMSG+"}, \"time\":\""+DateTime+"\"}");
	
	//Request to client
	if (client->put("http://localhost:8000/api/newdeveloper/schedules/"+strID, *schedEdit_msg)) {
		cout << "POST was successful" << endl;
	}

}
