//
// Created by Fran on 2017-11-25.
//

#ifndef V5_LIGHTWIDGET_H
#define V5_LIGHTWIDGET_H

#include <set>
#include <map>

#include <Wt/WContainerWidget>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/WSlider>
#include <Wt/WSelectionBox>
#include <Wt/WGridLayout>
#include <Wt/WPushButton>
#include <Wt/WButtonGroup>

#include "Light.h"

class Light;

class LightWidget: public Wt::WContainerWidget {

public:
    LightWidget(Wt::WContainerWidget *parent = 0);

private:
    /* Variables */
    std::map <std::string, Light> lights;
    std::set <std::string> lightIds;
    Light *currentLight;
    int numLights = 0;
    Wt::Http::Client *client;
    Wt::WText *selectionMessage;
    Wt::WText *lightInfoMessage;

    Wt::WSlider *briSlider;
    Wt::WSlider *hueSlider;
    Wt::WSlider *satSlider;
    Wt::WPushButton *onOffButton;
    Wt::WSelectionBox *selectionBox;
    Wt::WGridLayout *layout;
    Wt::WButtonGroup *group;

    /* Constants */
    const unsigned int BRI_MIN = 1;
    const unsigned int BRI_MAX = 254;
    const unsigned int HUE_MIN = 0;
    const unsigned int HUE_MAX = 65535;
    const unsigned int SAT_MIN = 0;
    const unsigned int SAT_MAX = 254;
    const unsigned int NME_MAX = 32;

    /* Functions */
    void getLights(boost::system::error_code err, const Wt::Http::Message& response);
    void getLightInfo(boost::system::error_code err, const Wt::Http::Message& response);
    void handleGetResponse(boost::system::error_code err, const Wt::Http::Message& response);
    void setBrightness();
    void setBrightness(unsigned int brightness);
    void setHue();
    void setHue(unsigned int hue);
    void setSat();
    void setSat(unsigned int sat);
    void onOff();
    void setOn(bool on);
    void lightSelected();
    void generateLightInfo();
    void changeTheme();

};

#endif //V5_LIGHTWIDGET_H
