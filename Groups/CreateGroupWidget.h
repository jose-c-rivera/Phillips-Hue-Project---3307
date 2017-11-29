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
#include <Wt/WLineEdit>
#include <Wt/WGridLayout>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Parser>
#include <Wt/Json/Value>


class Group;
class Light;

class CreateGroupWidget: public Wt::WContainerWidget{

	public:
		CreateGroupWidget(Wt::WContainerWidget *parent = 0);

	private:
		//Variables
	std::map <std::string, Light> lights;
	Wt::Http::Client *client;
	Wt::WPushButton *createGroupButton;
    	Wt::WSelectionBox *lightSelect;
    	Wt::WGridLayout *layout;
    	Wt::WLineEdit *groupName;
	int numLights;
	std::set <std::string> lightIds;
	Light* currentLights;

    	//Functions
    	void getLights(boost::system::error_code err, const Wt::Http::Message& response);
    	void creation(Light lights[], std::string groupName);
	void getCurrentSelection();


};
