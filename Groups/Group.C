
#include "Group.h"

class hueWidget;

using namespace std;

Group::Group(bool on, int brightness, int hue, int saturation, std::string name, std::string ID){

    this->on = on;
    this->bri = brightness;
    this->hue = hue;
    this->sat = saturation;
    this->name = name;
    this->ID = ID;

};

std::string Group::getID(){
	return ID;
}

string Group::getName(){
	return name;
}

bool Group::getOnOff(){
	return on;
}

int Group::getBright(){
	return bri;
}

int Group::getHue(){
	return hue;
}

int Group::getSat(){
	return sat;
}


void Group::setName(string newName){
	name = newName;
}

void Group::setBright(int bright){
	bri = bright;
}

void Group::setHue(int newHue){
	hue = newHue;
	
}

void Group::setSat(int newSat){
	sat = newSat;
}

void Group::setOnOff(bool newOn){
	on = newOn;
}

