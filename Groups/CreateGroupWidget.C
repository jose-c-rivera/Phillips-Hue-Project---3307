#include "CreateGroupWidget.h"

using namespace Wt;

extern std::string currentUser;

CreateGroupWidget::CreateGroupWidget(WContainerWidget *parent): WContainerWidget(parent){
	//Creates a new layout for the page
	layout = new Wt::WGridLayout();

	//Creates a new client for http requests
	client = new Wt::Http::Client(this);
	Wt::Http::Message *lights= new Wt::Http::Message();

	//Creates a textbox for the name of the group
	groupName = new WLineEdit();
	groupName -> setPlaceholderText("Please enter a name for this group");
	layout-> addWidget(groupName, 1, 1);

	//creates a multi-select box for adding lights to a group
	layout -> addWidget(new WText("Select Lights to add to a new group"), 0, 0);
	lightSelect = new WSelectionBox(); 
	layout -> addWidget(lightSelect, 0, 1);
	lightSelect -> setSelectionMode(Wt::SelectionMode::ExtendedSelection);

	//Creates and connects a push button to the create method
	createGroupButton = new WPushButton();
	layout -> addWidget(createGroupButton, 0, 2);
	createGroupButton->clicked().connect(std::bind([=]() {this, creation(currentLights, groupName->text().toUTF8()), lightSelect -> clearSelection();}));

	//Connects the client to the getLight method that populates the selection box
	client->done().connect(boost::bind(&CreateGroupWidget::getLights, this, _1, _2));
    if (client->get("http://localhost:8000/api/" + currentUser + "/lights")) {
        WApplication::instance()->deferRendering();
    }
    else {
        // in case of an error in the %URL
        std::cout << "error in URL of GET request" << std::endl;
    }
}

//Creates a new group using info passed to it
void CreateGroupWidget::creation(Light lights[], std::string groupName){
	Wt::Http::Message *msg = new Wt::Http::Message();
	int arraySize = sizeof(&lights)/sizeof(&lights[0]);
	msg -> addBodyText("{\"lights\": ["); 
	for(int i = 0; i < arraySize; i++){
		if(i < arraySize - 1){
		msg -> addBodyText (lights[i].getID() +", ");
		}
		else{
		msg ->addBodyText (lights[i].getID());		
		}
	}
	msg -> addBodyText("], \"name\":" + groupName + ", \"type\": LightGroup}");

	//Sends the new group to the bridge
	client->post("http://localhost:8000/api/"+ currentUser + "/groups", *msg);

}	
void CreateGroupWidget::getLights(boost::system::error_code err, const Wt::Http::Message& response){

	 if (!err && response.status() == 200) {
        std::cout << response.body() << std::endl;
        Json::Object result;
        Json::parse(response.body(), result);
        numLights = result.size();
        lightIds = result.names();

        /* Create all the light objects */
        for(std::string light: lightIds) {

            Json::Object tempObject = result.get(light);
            Json::Object lightState = tempObject.get("state");
            //Get light atrrib
            bool on = lightState.get("on").toBool();
            int bri = lightState.get("bri").toNumber();
            int hue = lightState.get("hue").toNumber();
            int sat = lightState.get("sat").toNumber();
            std::string alert = lightState.get("alert");
            std::string effect = lightState.get("effect");
            bool reachable = lightState.get("reachable").toBool();
            std::string name = tempObject.get("name");

            //Puts new lights in box
            Light *temp = new Light(on, bri, hue, sat, alert, effect, reachable, name, light);
            lights[temp->getName()] = *temp;

            lightSelect->addItem(temp->getName());
        }

        WApplication::instance()->resumeRendering();

	} 
}

void CreateGroupWidget::getCurrentSelection(){
	std::set<int> selection;
	selection  = lightSelect->selectedIndexes();
	currentLights = new Light[selection.size()];
	for(std::set<int>::iterator it = selection.begin(); it != selection.end(); it++){
		currentLights[*it] = lights[lightSelect->itemText(*it).toUTF8()];	
		
	}

	
}
  	
	




