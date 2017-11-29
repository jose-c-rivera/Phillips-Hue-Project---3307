/**
 * @file:	GroupWidget.C
 * @author:	Steven Crossma <scrossma@uwo.ca>
 * @date:	November 2017
 * @brief:	Widget that allows itneractions with groups
 */
#include "GroupWidget.h"

using namespace Wt;

extern std::string currentUser;

/**
 * @name:	Group Widget
 * @param:	Accepts a WContainerWidget to set as a parent of a widget
 * @brief:	Creates a Group Widget
 */
GroupWidget::GroupWidget(WContainerWidget *parent): WContainerWidget(parent){
	//creates a new layout for the widget
	layout = new Wt::WGridLayout();

	//creates a new client for http requests
	client = new Wt::Http::Client(this);

	Group currentGroup;

	//Add a selection box to the container
	layout -> addWidget(new WText("Select a group to change"), 0, 0);
	groupSelect = new WSelectionBox();
	layout -> addWidget(groupSelect, 0, 1);

	//Current Group Info
	Wt::WText *groupInfoLabel = new Wt::WText("<p>Group Information:</p>");
    groupInfoMessage = new WText("Group Info...");
    layout->addWidget(groupInfoLabel, 0, 1);
    layout->addWidget(groupInfoMessage, 1, 1);

    //Creates the slider for the brightness attribute
	bright = new WSlider(Wt::Orientation::Vertical);
	WText *briSliderLabel = new WText("<p>Light brightness:</p>");

	bright->setMinimum(0);
    bright->setMaximum(20);
    bright->setValue(10);
    bright->setTickInterval(5);
    bright->resize(300, 50);
    bright -> valueChanged().connect(std::bind([=](){setBright();}));
    bright ->setDisabled(true);

    layout->addWidget(briSliderLabel, 0, 2);
    layout->addWidget(bright, 1, 2);

    //Creates the slider for the hue attribute
	hue = new WSlider(Wt::Orientation::Vertical);
	WText *hueSliderLabel = new WText("<p>Light Hue:</p>");

	hue->setMinimum(0);
    hue->setMaximum(20);
    hue->setValue(10);
    hue->setTickInterval(5);
    hue->resize(300, 50);
    hue -> valueChanged().connect(std::bind([=](){setHue();}));
    hue ->setDisabled(true);

    layout->addWidget(hueSliderLabel, 0, 3);
    layout->addWidget(hue, 1, 3);

    //Creates the slider for the saturation attribute
	sat = new WSlider(Wt::Orientation::Vertical);
	WText *satSliderLabel = new WText("<p>Light Saturation:</p>");

	sat ->setMinimum(0);
    sat ->setMaximum(20);
    sat ->setValue(10);
    sat ->setTickInterval(5);
    sat ->resize(300, 50);
	sat ->valueChanged().connect(std::bind([=](){setSat();}));
	sat ->setDisabled(true);

	layout->addWidget(satSliderLabel, 0, 4);
    layout->addWidget(sat, 1, 4);

    //Creates an on and off button that alternates based on what it is currently
    onOffButton = new WPushButton();
    onOffButton->clicked().connect(this, &GroupWidget::onOff);
    layout->addWidget(onOffButton, 0, 5);

    //Finds all of the groups and populates the select box
    client->done().connect(boost::bind(&GroupWidget::getGroups, this, _1, _2));
    if (client->get("http://localhost:8000/api/" + currentUser + "/groups")) {
        WApplication::instance()->deferRendering();
    }
    else {
        // in case of an error in the %URL
        std::cout << "error in URL of GET request" << std::endl;
    }
}

/**
 * @name:  getGroups()
 * @param: Takes an error code and an http response
 * @brief: Gets the groups from the bridge and stores them in a select box
 */
void GroupWidget::getGroups(boost::system::error_code err, const Wt::Http::Message& response) {
    if (!err && response.status() == 200) {
        std::cout << response.body() << std::endl;
        Json::Object result;
        Json::parse(response.body(), result);

        groupIds = result.names();
        for(std::string group: groupIds) {
        	//Gets the group attributes
           Json::Object tempObject = result.get(group);
           Json::Object groupState = tempObject.get("action");

           bool on = groupState.get("on").toBool();
           int bri = groupState.get("bri").toNumber();
           int hue = groupState.get("hue").toNumber();
           int sat = groupState.get("sat").toNumber();
           std::string name = tempObject.get("name");
          
           Group *temp = new Group(on, bri, hue, sat, name, group);
           groups[temp->getName()] = *temp;

           groupSelect->addItem(temp->getName());


        }
          WApplication::instance()->resumeRendering();
    }
    else{
    	std::cout << "ERROR GETTING GROUPS" << std::endl;
        WApplication::instance()->resumeRendering();
    }

    groupSelect->setCurrentIndex(0);
    GroupWidget::groupSelected();
}

/**
 * @name:  setBright()
 * @brief: Takes the new brightness when the slider is moved and transfers to bridge
 */
void GroupWidget::setBright(){

	std::string newBrightness = std::to_string(GroupWidget::bright->value());

    Http::Message *brightnessMessage = new Http::Message();
    brightnessMessage->addBodyText("{\"bri\":\"");
    brightnessMessage->addBodyText(newBrightness);
    brightnessMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/" + currentUser + "/groups/" + currentGroup.getID() + "/action";

    GroupWidget::client->put(url, *brightnessMessage);

    currentGroup.setBright(bright->value());

    delete brightnessMessage;
}

/**
 * @name:  setHue()
 * @brief: Takes the new hue when the slider is moved and transfers to the bridge
 */
void GroupWidget::setHue() {

    std::string newHue = std::to_string(GroupWidget::hue->value());

    Http::Message *hueMessage = new Http::Message();
    hueMessage->addBodyText("{\"hue\":\"");
    hueMessage->addBodyText(newHue);
    hueMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/" + currentUser + "/groups/" + currentGroup.getID() + "/action";

    GroupWidget::client->put(url, *hueMessage);

    currentGroup.setHue(hue->value());

    delete hueMessage;
}

/**
 * @name:  setSat()
 * @brief: Takes the new saturation when the slider is moved and transfers to the bridge
 */
void GroupWidget::setSat() {

    std::string newSat = std::to_string(GroupWidget::sat->value());

    Http::Message *satMessage = new Http::Message();
    satMessage->addBodyText("{\"sat\":\"");
    satMessage->addBodyText(newSat);
    satMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/" + currentUser + "/groups/" + currentGroup.getID() + "/action";

    GroupWidget::client->put(url, *satMessage);

    currentGroup.setSat(sat->value());

    delete satMessage;
}

/**
 * @name:  onOff()  
 * @brief: Turns the group on or off and inverts the button
 */
void GroupWidget::onOff() {

    Http::Message *onOffMessage = new Http::Message();

    //If the current group is on, turn them off and display on for next time
    if (currentGroup.getOnOff()) {
        onOffMessage->addBodyText("{\"on\":\"false\"}");
        currentGroup.setOnOff(false);
        onOffButton->setText("Turn ON");
    }
    //If the current group is off, turn them on and display off for next time
    else {
        onOffMessage->addBodyText("{\"on\":\"true\"}");
        currentGroup.setOnOff(true);
        onOffButton->setText("Turn OFF");
    }

    std::string url = "http://localhost:8000/api/" + currentUser + "/groups/" + currentGroup.getID() + "/action";

    GroupWidget::client->put(url, *onOffMessage);

    delete onOffMessage;
}

/**
 * @name:  groupSelected()
 * @brief: Gets the current group that is selected in the select box
 */
void GroupWidget::groupSelected() {
    currentGroup = groups[groupSelect->currentText().toUTF8()];

    if (currentGroup.getOnOff()) {
        onOffButton->setText("Turn OFF");
    }
    else {
        onOffButton->setText("Turn ON");
    }

    bright->setValue(currentGroup.getBright());
    hue->setValue(currentGroup.getHue());
    sat->setValue(currentGroup.getSat());

    GroupWidget::generateGroupInfo();
}

//Deletes the current group
/*void GroupWidget::deleteGroup(){
	GroupWidget::client->deleteRequest("http://localhost:8000/api/" + currentUser + "/groups/" + std::to_string(currentGroup.getID()));

	std::set<int> selection;
	selection  = groupSelect->selectedIndexes();
	for(std::set<int>::iterator it = selection.begin(); it != selection.end(); it++){
		GroupWidget::groupSelect->removeItem(*it);
	}
	
}*/

/**
 * @name:  generateGroupInfo()
 * @brief: Prints out some of the information about the current group
 */
void GroupWidget::generateGroupInfo() {
    std::string s = "<p>Name: " + currentGroup.getName() + "</p><p>Brightness: " + std::to_string(currentGroup.getBright());
    groupInfoMessage->setText(s);
}


