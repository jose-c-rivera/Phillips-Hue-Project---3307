#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <stdlib.h>

class hueWidget;
class Light;

class Group {
public:
    /*Constructors*/
    Group();              
    Group(bool on, int brightness, int hue, int saturation, std::string name, std::string ID);
                            

    /* Getters */
    bool getOnOff();
    int getBright();
    int getHue();
    int getSat();
    std::string getName();
    std::string getID();
   
    /* Setters */
    void setOnOff(bool newOn);
    void setBright(int newBrightness);
    void setHue(int newHue);
    void setSat(int newSaturation);
    void setName(std::string newName);

private:

    /* group Attributes */
    bool on;
    int bri;
    int hue;
    int sat;
    std::string name;
    std::string ID;

};

#endif //GROUP_H
