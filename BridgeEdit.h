#ifndef GROUP_BRIDGEEDIT_H
#define GROUP_BRIDGEEDIT_H

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <string>
#include <Wt/WText>


//class Bridge;

class BridgeEdit : public Wt::WContainerWidget{
public:
	BridgeEdit(Wt::WContainerWidget *parent = 0);
private:
	Wt::WLineEdit *bridge_name_edit;			//Inputs
	Wt::WLineEdit *location_edit;
	Wt::WLineEdit *IP_address_edit;
	Wt::WLineEdit *portnum_edit;
	Wt::WText *blankSpace;			//Where to print info

	void bridge_app();
};

#endif //GROUP_HUEWIDGET_H