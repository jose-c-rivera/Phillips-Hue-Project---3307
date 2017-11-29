/**
 * ManageWidget.C
 *
 * Author: Mike Davis
 *
 * Implementation file for LightWidget.
 *
 * The LightWidget class allows the user to view and modify light elements.
 */
#include <vector>
#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include "ManageWidget.h"
#include "database.C"

using namespace std;
using namespace Wt;
extern string currentUser;

ManageWidget::ManageWidget(std::string currentUser, WContainerWidget *parent)
        : WContainerWidget(parent){
    WContainerWidget *manageContainer = new WContainerWidget();
    manageContainer->addStyleClass("manageContainer");

    //vector<Bridge> bridgeList;
    for(int x = 0; x < 4; x++){
    	WContainerWidget *bridgeContainer = new WContainerWidget();
    	bridgeContainer->addStyleClass("bridgeContainer");
        string bridgeinfo = "Bridge ID: " + to_string(x);
    	bridgeContainer->addWidget(new WText(bridgeinfo));
    	//bridgeContainer.addWidget(new WText(bridgeList[i].getBridgeName));
    	manageContainer->addWidget(bridgeContainer);
    	WContainerWidget *lightsContainer = new WContainerWidget();
    	lightsContainer->addStyleClass("lightsContainer");
        lightsContainer->addWidget(new WText("Bridge Lights:"));
    	manageContainer->addWidget(lightsContainer);

    	for (int i = 0; i < 2; ++i)
    	{
    		WContainerWidget *sLightContainer = new WContainerWidget();
    		sLightContainer->addStyleClass("sLight");
            string lightinfo = "Light ID: " + to_string(x) + to_string(i);
    		sLightContainer->addWidget(new WText(lightinfo));
    		lightsContainer->addWidget(sLightContainer);
    	}

    }

    addWidget(manageContainer);
}

//std::vector<User> ManageWidget::bridges(){

