/**
 * Light.C
 *
 * This class represents a light object.
 *
 */

#include <iostream>
//#include <Wt/Http/Client>
//#include <Wt/Http/Message>
#include "Light.h"
//#include "hueWidget.h"

class hueWidget;

using namespace std;

/**
 * Light()
 *
 * Constructor
 */
Light::Light() {
    cout << "Light Object created" << endl;
}

Light::Light(bool on, int brightness, int hue, int saturation, std::string alert, std::string effect, bool reachable, std::string name, std::string ID) {
    this->on = on;
    this->bri = brightness;
    this->hue = hue;
    this->sat = saturation;
    this->alert = alert;
    this->effect = effect;
    this->reachable = reachable;
    this->name = name;
    this->ID = ID;
}

/**
 * ~Light()
 *
 * Destructor
 */
Light::~Light() {
    //empty destructor
    cout << "Destructor called on Light Object" << endl;
}

/**
 * getOn()
 *
 * Checks to see if the light is on or not.
 *
 * @return true if the light is on and false otherwise
 */
bool Light::getOn() {
    return on;
}

unsigned int Light::getBrightness() {
    return bri;
}

unsigned int Light::getHue() {
    return hue;
}

unsigned int Light::getSaturation() {
    return sat;
}

std::string Light::getAlert() {
    return alert;
}

std::string Light::getEffect() {
    return effect;
}

bool Light::getReachable() {
    return reachable;
}

std::string Light::getName() {
    return name;
}

std::string Light::getID() {
    return ID;
}

void Light::setOn(bool newOn) {
//    Wt::Http::Message *msg = new Wt::Http::Message();
//
//    if (newOn) {
//        msg->addBodyText("{\"on\":true}");
//    }
//    else {
//        msg->addBodyText("{\"on\":false}");
//    }
//    hueWidget::client->put("http://localhost:8000/api/newdeveloper/lights/1/state", *msg);

    on = newOn;

}

void Light::setBrightness(unsigned int newBrightness) {
    bri = newBrightness;
}

void Light::setHue(unsigned int newHue) {
    hue = newHue;
}

void Light::setSaturation(unsigned int newSaturation) {
    sat = newSaturation;
}

void Light::setAlert(std::string newAlert) {
    alert = newAlert;
}

void Light::setEffect(std::string newEffect) {
    effect = newEffect;
}

void Light::setReachable(bool newReachable) {
    reachable = newReachable;
}

void Light::setName(std::string newName) {
    name = newName;
}

void Light::setID(std::string ID) {
    this->ID = ID;
}