#ifndef GROUP_BRIDGEEDIT_H
#define GROUP_BRIDGEEDIT_H

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <string>
#include <Wt/WText>

class BridgeEdit : public Wt::WContainerWidget{
public:
	BridgeEdit(Wt::WContainerWidget *parent = 0);
private:
	WLineEdit *bridge_name_edit;			//Inputs
	WLineEdit *location_edit;
	WLineEdit *IP_address_edit;
	WLineEdit *portnum_edit;
	WText *blankSpace;			//Where to print info

	void bridge_app();
}

#endif //GROUP_HUEWIDGET_H