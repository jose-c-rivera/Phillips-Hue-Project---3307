/*
 * File: bridge.C
 * Purpose: Class to represent a bridge
 * Language: C++
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

using namespace std;
using namespace Wt;

class BridgeWidget::BridgeWidget()
	: WCompositeWidget()
{
	public: 
		bridgeEdit(const WEnvironment& env);
	private:
		WLineEdit *bridge_name_edit;			//Inputs
		WLineEdit *location_edit;
		WLineEdit *IP_address_edit;
		WLineEdit *portnum_edit;

		WText *blankSpace;			//Where to print info
		//WText *blankSpaceA;
	void bridge_app();
};

bridgeEdit::bridgeEdit(const WEnvironment& env) : WApplication(env) {
	setTitle("Bridge Edit");						//Title
	root()->addWidget(new WText("Input name of the bridge: "));		//Shown Text.
	bridge_name_edit = new WLineEdit(root());				//Text input
	bridge_name_edit->setFocus();						//F O C U S 
	
	//Bridge myBridge; Tried passing bridge object

	WPushButton *button = new WPushButton("Set Name", root());		//Button
	button->setMargin(5, Left);						//Make it look fresh

	root()->addWidget(new WBreak());					//line break

	button->clicked().connect(this, &bridgeEdit::bridge_app);		//connect through with button/enter press
	bridge_name_edit->enterPressed().connect(boost::bind(&bridgeEdit::bridge_app, this));

//-------------------------------------------------------------

	root()->addWidget(new WText("Input location of the bridge: "));	
	location_edit = new WLineEdit(root());		
	location_edit->setFocus();				

	WPushButton *buttonA = new WPushButton("Set Location", root());	
	buttonA->setMargin(5, Left);		

	root()->addWidget(new WBreak());	
	
	buttonA->clicked().connect(this, &bridgeEdit::bridge_app);		
	location_edit->enterPressed().connect(boost::bind(&bridgeEdit::bridge_app, this));

//-------------------------------------------------------------
	root()->addWidget(new WText("Input IP Address of the bridge: "));	
	IP_address_edit = new WLineEdit(root());		
	IP_address_edit->setFocus();				 

	WPushButton *buttonB = new WPushButton("Set Location", root());	
	buttonB->setMargin(5, Left);		

	root()->addWidget(new WBreak());	

	buttonB->clicked().connect(this, &bridgeEdit::bridge_app);		
	IP_address_edit->enterPressed().connect(boost::bind(&bridgeEdit::bridge_app, this));

//-------------------------------------------------------------

	root()->addWidget(new WText("Input port number of the bridge: "));		
	portnum_edit = new WLineEdit(root());		
	portnum_edit->setFocus();	
			
	WPushButton *buttonC = new WPushButton("Set Location", root());	
	buttonC->setMargin(5, Left);		

	root()->addWidget(new WBreak());	
	blankSpace = new WText(root());						//Blank and waiting to fill up

	buttonC->clicked().connect(this, &bridgeEdit::bridge_app);		
	portnum_edit->enterPressed().connect(boost::bind(&bridgeEdit::bridge_app, this));


}
//Could just have different methods, all doing their own edits.
//Since changing one changes them all.
//Trying to pass a Bridge object into method: unsuccessful
void bridgeEdit::bridge_app(){
	
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
	blankSpace->setText(myBridge.getBridgeName() + "<br />" + myBridge.getBridgeLocation()
	 + "<br />" + myBridge.getIPAddress() + "<br />" + myBridge.getPortNum());

}





