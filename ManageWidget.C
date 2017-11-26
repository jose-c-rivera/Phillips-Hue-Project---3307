//Displays the account information

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

using namespace std;
using namespace Wt;

ManageWidget::ManageWidget(std::string userid, WContainerWidget *parent)
        : WContainerWidget(parent){

    WContainerWidget *manageContainer = new WContainerWidget();
    manageContainer->addStyleClass("manageContainer");

    //vector<Bridge> bridgeList;
    for(int x = 0; x < 4; x++){
    	WContainerWidget *bridgeContainer = new WContainerWidget();
    	bridgeContainer->addStyleClass("bridgeContainer");
    	bridgeContainer->addWidget(new WText("Bridge ID: "));
    	//bridgeContainer.addWidget(new WText(bridgeList[i].getBridgeName));
    	manageContainer->addWidget(bridgeContainer);

    	WContainerWidget *lightsContainer = new WContainerWidget();
    	lightsContainer->addStyleClass("lightsContainer");
    	lightsContainer->addWidget(new WText("Bridge Lights: "));
    	manageContainer->addWidget(lightsContainer);

    	for (int i = 0; i < 2; ++i)
    	{
    		WContainerWidget *sLightContainer = new WContainerWidget();
    		sLightContainer->addStyleClass("sLight");
    		sLightContainer->addWidget(new WText("Light ID: "));
    		lightsContainer->addWidget(sLightContainer);
    	}
    }

    addWidget(manageContainer);

}