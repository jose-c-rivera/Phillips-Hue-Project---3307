/*
 * File: bridge.C
 * Purpose: Class to represent a bridge
 * Language: C++
 * Author: Mike Davis , Jose Rivera, Allan Rashad Khan
*/

#include <string>
#include <iostream>
#include <stdlib.h>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WCompositeWidget>
#include <Wt/WMessageBox>
#include "BridgeEdit.h"
#include "database.C"

using namespace std;
using namespace Wt;

extern string currentUser;

BridgeEdit::BridgeEdit(WContainerWidget *parent):
	WContainerWidget(parent)
{
	addStyleClass("bridgeedit");

        Database* bridgeDB = new Database();

	addWidget(new WText("<h3>Add Bridge</h3>"));
	
	WLineEdit *bridgeName = new WLineEdit(this);				
	bridgeName->setPlaceholderText("Bridge Name");
	bridgeName->setFocus();						
	addWidget(new WText("<p></p>"));

//-------------------------------------------------------------

	WLineEdit *bridgeLocation = new WLineEdit(this);			
	bridgeLocation->setPlaceholderText("Bridge Location");
	addWidget(new WText("<p></p>"));	

//-------------------------------------------------------------

	WLineEdit *bridgeIP = new WLineEdit(this);		
	bridgeIP->setPlaceholderText("Bridge IP");				 
	addWidget(new WText("<p></p>"));

//-------------------------------------------------------------
	
	WLineEdit *bridgePort = new WLineEdit(this);		
	bridgePort->setPlaceholderText("Bridge Port");
	addWidget(new WText("<p></p>"));

	WPushButton *addBridge = new WPushButton("Add Port",this);	
	addBridge->setMargin(5, Left);	


        addBridge->clicked().connect(std::bind([=]() {
		bridgeDB->registerBridge(
			bridgeName->text().toUTF8(),
 			bridgeLocation->text().toUTF8(),
 			bridgeIP->text().toUTF8(),
 			bridgePort->text().toUTF8(),
 			currentUser);
        }));




	addWidget(new WText("<h3>Edit Bridge</h3>"));

	addWidget(new WText("Input name of bridge to Edit: "));	
	WLineEdit* bridge_focus = new WLineEdit(this);
	
	addWidget(new WText("<p></p>"));
	addWidget(new WText("Input location of the bridge: "));	
	location_edit = new WLineEdit(this);						

	WPushButton *button_location_edit = new WPushButton("Edit Location", this);	
	button_location_edit->setMargin(5, Left);			
	
        button_location_edit->clicked().connect(std::bind([=]() {
		bridgeDB->modifyBLocation(
			bridge_focus->text().toUTF8(), 
			location_edit->text().toUTF8());
        }));

//-------------------------------------------------------------
	addWidget(new WText("<p></p>"));
	addWidget(new WText("Input IP Address of the bridge: "));	
	IP_address_edit = new WLineEdit(this);		
	IP_address_edit->setFocus();				 

	WPushButton *button_address_edit = new WPushButton("Edit IP", this);	
	button_address_edit->setMargin(5, Left);			

	button_address_edit->clicked().connect(std::bind([=]() {
		bridgeDB->modifyBAddress(
			bridge_focus->text().toUTF8(), 
			IP_address_edit->text().toUTF8());
        }));


//-------------------------------------------------------------
	addWidget(new WText("<p></p>"));
	addWidget(new WText("Input port number of the bridge: "));		
	portnum_edit = new WLineEdit(this);		
	portnum_edit->setFocus();	
			
	WPushButton *button_portnum_edit = new WPushButton("Edit Port",this);	
	button_portnum_edit->setMargin(5, Left);		

	addWidget(new WBreak());	

	button_portnum_edit->clicked().connect(std::bind([=]() {
		bridgeDB->modifyBPortNum(
			bridge_focus->text().toUTF8(), 
			portnum_edit->text().toUTF8());
        }));


}
//Could just have different methods, all doing their own edits.
//Since changing one changes them all.
//Trying to pass a Bridge object into method: unsuccessful
void BridgeEdit::bridge_app(){
	/*
	Bridge myBridge;					//Bridge object
	WString convName = bridge_name_edit->text();		//Convert them into
	WString convLoc = location_edit->text();		//Something to work with
	WString convIP = IP_address_edit->text();
	WString convPort = portnum_edit->text();

	myBridge.setBridgeName(convName);			//Set them
	myBridge.setBridgeLocation(convLoc);			//Setting 1 sets the rest**
	myBridge.setIPAddress(convIP);
	myBridge.setPortNum(convPort);

	//Show it on screen for debugging
	//blankSpace->setText(myBridge.getBridgeName() + "<br />" + myBridge.getBridgeLocation()
	// + "<br />" + myBridge.getIPAddress() + "<br />" + myBridge.getPortNum());*/

}





