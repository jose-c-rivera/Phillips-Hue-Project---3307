//Light.h
//
// Created by mike on 20/11/17.
//

#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include <Wt/Http/Message>
#include "hueWidget.h"

class hueWidget;

class Light {
public:
    Light();                                //Constructor
    Light(bool on, int brightness, int hue, int saturation, std::string alert, std::string effect, bool reachable, std::string name, std::string ID);
    ~Light();                               //Destructor

    /* Getters */
    bool getOn();
    unsigned int getBrightness();
    unsigned int getHue();
    unsigned int getSaturation();
    std::string getAlert();
    std::string getEffect();
    bool getReachable();
    std::string getName();
    std::string getID();

    /* Setters */
    void setOn(bool newOn);
    void setBrightness(unsigned int newBrightness);
    void setHue(unsigned int newHue);
    void setSaturation(unsigned int newSaturation);
    void setAlert(std::string newAlert);
    void setEffect(std::string newEffect);
    void setReachable(bool newReachable);
    void setName(std::string newName);
    void setID(std::string ID);

private:

//    const unsigned int NAME_MAX = 32;

    /* Light Attributes */
    bool on;
    unsigned int bri;
    unsigned int hue;
    unsigned int sat;
    std::string alert;
    std::string effect;
    bool reachable;
    std::string name;
    std::string ID;

};

#endif //LIGHT_H
