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
#include <Wt/WSlider>
#include <Wt/WGridLayout>

using namespace std;
using namespace Wt;
string currentUser = "newdeveloper";	//CHANGE THIS

class groups : public WApplication{
	public:
		Http::Client *client = new Http::Client(this);
		groups(const WEnvironment& env);
		Http::Message *response = new Http::Message();
		WButtonGroup *group = new WButtonGroup(this);
		WButtonGroup *groupB = new WButtonGroup(this);
		WButtonGroup *groupC = new WButtonGroup(this);
		WButtonGroup *groupD = new WButtonGroup(this);
		WSlider *briSlider = new WSlider(Wt::Vertical);
		WSlider *hueSlider = new WSlider(Wt::Vertical);
		WSlider *satSlider = new WSlider(Wt::Vertical);
		
	private:
		WLineEdit *name;
		WLineEdit *IDNum;
		WLineEdit *light1;
		WLineEdit *light2;
		WLineEdit *date;
		WLineEdit *time;
		WLineEdit *bri;
		WLineEdit *hue;
		WText *blank;
	void groupSET();
	void handleHttpResponse(boost::system::error_code err, const Http::Message& response);		
};

groups::groups(const WEnvironment& env) : WApplication(env){
	root()->addWidget(new WText("Name of group"));
	name = new WLineEdit(root());
	new WBreak(root());
/*	
	root()->addWidget(new WText("ON OR OFF"));
	WLineEdit onOff = new WLineEdit(root());
	new WBreak(root());

	root()->addWidget(new WText("bri"));
	WLineEdit bri = new WLineEdit(root());
	new WBreak(root());

	root()->addWidget(new WText("hue"));
	WLineEdit hue = new WLineEdit(root());
	new WBreak(root());

	root()->addWidget(new WText("sat"));
	WLineEdit sat = new WLineEdit(root());
	new WBreak(root());
*/
	root()->addWidget(new WText("light 1"));
	light1 = new WLineEdit(root());
	new WBreak(root());

	root()->addWidget(new WText("light 2"));
	light2 = new WLineEdit(root());
	new WBreak(root());

	WPushButton *finalbutton = new WPushButton("Create Group", root());
	finalbutton->clicked().connect(this,&groups::groupSET);
}

void groups::groupSET(){
	string strName = (name->text()).toUTF8();
	//string strON = (onOff->text()).toUTF8();

	//string strBri = (bri->valueText()).toUTF8();
	//string strHue = (hue->valueText()).toUTF8();
	//string strSat = (sat->valueText()).toUTF8();

	string strLight1 = (light1->valueText()).toUTF8();
	string strLight2 = (light2->valueText()).toUTF8();

	string LightArray = "[ \""+strLight1+"\",\""+strLight2+"\"]";

	Http::Message *msg = new Http::Message();	
	string temp = "{ \"ights\":"+LightArray+", \"name\": \""+strName+"\"}";

	msg->addBodyText(temp);
	if (client->post("http://localhost:8000/api/newdeveloper/groups", *msg)) {
		cout << "POST was successful" << endl;
	}

}

WApplication *createApplication(const WEnvironment& env){
	return new groups(env);
}


int main (int argc, char **argv){
	//Wt stuff again from Hello.C example
	return WRun(argc, argv, &createApplication);
	
}

