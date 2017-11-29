/**
 * @file   Group.C
 * @Author Steven Crossman <scrossma@uwo.ca>
 * @date   November 2017
 * @brief  Group class that imitates the emulator
 */

#include "Group.h"

/**
 * @name:  Group()
 * @param: Accepts a on/off boolean, the original brightness, the original hue, the original saturation, the original name, and the id of the group
 * @brief: Creates a group of lights
 */
Group::Group(bool on, int brightness, int hue, int saturation, std::string name, std::string ID){

    this->on = on;
    this->bri = brightness;
    this->hue = hue;
    this->sat = saturation;
    this->name = name;
    this->ID = ID;

};

/**
 * @name:  getID()
 * @brief: Returns the group ID
 */
std::string Group::getID(){
	return ID;
}

/**
 * @name:  getName()
 * @brief: Returns the group Name
 */
std::string Group::getName(){
	return name;
}

/**
 * @name:  getOnOff()
 * @brief: Returns the group on/off status
 */
bool Group::getOnOff(){
	return on;
}

/**
 * @name:  getBright()
 * @brief: Returns the group brightness
 */
int Group::getBright(){
	return bri;
}

/**
 * @name:  getHue()
 * @brief: Returns the group Hue
 */
int Group::getHue(){
	return hue;
}

/**
 * @name:  getSat()
 * @brief: Returns the group Saturation
 */
int Group::getSat(){
	return sat;
}

/**
 * @name:  setName()
 * @brief: Takes a new name and renames the group
 */
void Group::setName(std::string newName){
	name = newName;
}

/**
 * @name:  setBright()
 * @brief: Changes the brightness of the group
 */
void Group::setBright(int bright){
	bri = bright;
}

/**
 * @name:  setHue()
 * @brief: Changes the hue of the group
 */
void Group::setHue(int newHue){
	hue = newHue;
	
}

/**
 * @name:  setSat()
 * @brief: Changes the saturation of the group
 */
void Group::setSat(int newSat){
	sat = newSat;
}

/**
 * @name:  setOnOff()
 * @brief: Changes the on/off status of the group
 */
void Group::setOnOff(bool newOn){
	on = newOn;
}

