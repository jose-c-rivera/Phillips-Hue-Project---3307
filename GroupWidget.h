/**
 * @file   GroupWidget.h
 * @Author Steven Crossman <scrossma@uwo.ca>
 * @date   November 2017
 * @brief  Header for GroupWidget
 */
#include <set>
#include <map>
#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WSelectionBox>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/WSlider>
#include <Wt/WGridLayout>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Parser>
#include <Wt/Json/Value>
#include <Wt/WString>

class Group;

/**
 * @name:  GroupWidget()
 * @param: Accepts a WContainerWidget to set as parent of widget
 * @brief: Declares a GroupWidget
 */
class GroupWidget: public Wt::WContainerWidget{

	public:
	//Constructor	
    GroupWidget(Wt::WContainerWidget *parent = 0);

	private:
	//Variables 
    Group currentGroup;
    std::map <std::string, Group> groups;
    std::set <std::string> groupIds;
    Wt::Http::Client *client;
    Wt::WText *groupInfoMessage;
    Wt::WSlider *bright;
    Wt::WSlider *hue;
    Wt::WSlider *sat;
    Wt::WPushButton *onOffButton;
    Wt::WSelectionBox *groupSelect;
    Wt::WGridLayout *layout;


    /* Constants */
    const unsigned int BRI_MIN = 1;
    const unsigned int BRI_MAX = 254;
    const unsigned int HUE_MIN = 0;
    const unsigned int HUE_MAX = 65535;
    const unsigned int SAT_MIN = 0;
    const unsigned int SAT_MAX = 254;
    const unsigned int NME_MAX = 32;	

	//Functions
    void getGroups(boost::system::error_code err, const Wt::Http::Message& response);
    void getGroupInfo(boost::system::error_code err, const Wt::Http::Message& response);
    void handleGetResponse(boost::system::error_code err, const Wt::Http::Message& response);
    void setBright();
    void setHue();
    void setSat();
    void onOff();
    void groupSelected();
    void generateGroupInfo();
    //void deleteGroup();

};
