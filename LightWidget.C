/**
 * LightWidget.C
 *
 * Author: Fran Plancke, Mike Davis
 *
 * Implementation file for LightWidget.
 *
 * The LightWidget class allows the user to view and modify light elements.
 */

#include <string>
#include <iostream>
#include <map>

#include <Wt/WApplication>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/WSlider>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Parser>
#include <Wt/Json/Value>
#include <Wt/WString>
#include <Wt/WSelectionBox>
#include <Wt/WGridLayout>
#include <Wt/WGroupBox>
#include <Wt/WButtonGroup>
#include <Wt/WRadioButton>
#include <Wt/WBreak>

#include "LightWidget.h"

using namespace Wt;

/**
 * LightWidget()
 *
 * Constructor for a LightWidget
 *
 * @param parent the parent container
 */
LightWidget::LightWidget(WContainerWidget *parent)
        : WContainerWidget(parent){

    layout = new Wt::WGridLayout();

    //CSS
    addStyleClass("light_container");

    //Creat an Http Client to send Http requests
    client = new Wt::Http::Client(this);
    Wt::Http::Message *msg = new Wt::Http::Message();

    // Light Selection Box
    selectionMessage = new WText("<p>Light:</p>");
    layout->addWidget(selectionMessage, 0, 0);

    selectionBox = new Wt::WSelectionBox(this);
    selectionBox->activated().connect(this, &LightWidget::lightSelected);

    layout->addWidget(selectionBox, 1, 0);

    //Light Info
    Wt::WText *lightInfoLabel = new Wt::WText("<p>Light Information:</p>");
    lightInfoMessage = new WText("Light Info...");

    layout->addWidget(lightInfoLabel, 0, 1);
    layout->addWidget(lightInfoMessage, 1, 1);

    //Brightness Slider
    WText *briSliderLabel = new WText("<p>Light brightness:</p>");

    briSlider = new WSlider(Wt::Vertical);
    briSlider->setMinimum(BRI_MIN);
    briSlider->setMaximum(BRI_MAX);
    briSlider->setValue(127);
    briSlider->resize(50, 200);
    briSlider->valueChanged().connect(this, &LightWidget::setBrightness);

    layout->addWidget(briSliderLabel, 0, 2);
    layout->addWidget(briSlider, 1, 2);

    //Hue Slider
    WText *hueSliderLabel = new WText("<p>Light hue:</p>");

    hueSlider = new WSlider(Wt::Vertical);
    hueSlider->setMinimum(HUE_MIN);
    hueSlider->setMaximum(HUE_MAX);
    hueSlider->setValue(32767);
    hueSlider->resize(50, 200);
    hueSlider->valueChanged().connect(this, &LightWidget::setHue);

    layout->addWidget(hueSliderLabel, 0, 3);
    layout->addWidget(hueSlider, 1, 3);

    //Saturation Slider
    WText *satSliderLabel = new WText("<p>Light saturation:</p>");

    satSlider = new WSlider(Wt::Vertical);
    satSlider->setMinimum(SAT_MIN);
    satSlider->setMaximum(SAT_MAX);
    satSlider->setValue(127);
    satSlider->resize(50, 200);
    satSlider->valueChanged().connect(this, &LightWidget::setSat);

    layout->addWidget(satSliderLabel, 0, 4);
    layout->addWidget(satSlider, 1, 4);

    /* On/Off Button */
    onOffButton = new WPushButton();
    onOffButton->clicked().connect(this, &LightWidget::onOff);
    layout->addWidget(onOffButton, 0, 5);

    setLayout(layout);

    //Themes
    enum Theme { None = 1, Christmas = 2, Halloween = 3, Easter = 4 };
    // use a group box as widget container for 4 radio buttons, with a title
    Wt::WGroupBox *container = new Wt::WGroupBox("Theme:");
    // use a button group to logically group the 3 options
    group = new Wt::WButtonGroup(this);

    Wt::WRadioButton *button;

    button = new Wt::WRadioButton("No Theme", container);
    new Wt::WBreak(container);
    group->addButton(button, None);
    group->button(None)->checked().connect(this, &LightWidget::changeTheme);

    button = new Wt::WRadioButton("Christmas", container);
    new Wt::WBreak(container);
    group->addButton(button, Christmas);
    group->button(Christmas)->checked().connect(this, &LightWidget::changeTheme);

    button = new Wt::WRadioButton("Halloween", container);
    new Wt::WBreak(container);
    group->addButton(button, Halloween);
    group->button(Halloween)->checked().connect(this, &LightWidget::changeTheme);

    button = new Wt::WRadioButton("Easter", container);
    new Wt::WBreak(container);
    group->addButton(button, Easter);
    group->button(Easter)->checked().connect(this, &LightWidget::changeTheme);

    group->setCheckedButton(group->button(None));

    layout->addWidget(container, 1, 5);

    /* Get the info for all of the lights for the bridge */
    client->done().connect(boost::bind(&LightWidget::getLights, this, _1, _2));
    if (client->get("http://localhost:8000/api/newdeveloper/lights")) {
        WApplication::instance()->deferRendering();
    }
    else {
        // in case of an error in the %URL
        std::cout << "error in URL of GET request" << std::endl;
    }
}

/**
 * getLights()
 *
 * This function processes a response from a GET call to the hue bridge.
 * It identifies all of the lights for a given bridge.
 *
 * @param err
 * @param response the response from the GET call.
 */
void LightWidget::getLights(boost::system::error_code err, const Wt::Http::Message& response) {

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

            bool on = lightState.get("on").toBool();
            int bri = lightState.get("bri").toNumber();
            int hue = lightState.get("hue").toNumber();
            int sat = lightState.get("sat").toNumber();
            std::string alert = lightState.get("alert");
            std::string effect = lightState.get("effect");
            bool reachable = lightState.get("reachable").toBool();
            std::string name = tempObject.get("name");

            Light *temp = new Light(on, bri, hue, sat, alert, effect, reachable, name, light);
            lights[temp->getName()] = *temp;

            selectionBox->addItem(temp->getName());
        }

        WApplication::instance()->resumeRendering();

    }
    else {
        std::cout << "ERROR GETTING LIGHTS" << std::endl;
        WApplication::instance()->resumeRendering();
    }

    selectionBox->setCurrentIndex(0);
    LightWidget::lightSelected();

}

/**
 * setBrightness()
 *
 * Sets the brightness of the current light based on the slider value.
 */
void LightWidget::setBrightness() {

    std::string newBrightness = std::to_string(LightWidget::briSlider->value());

    Http::Message *brightnessMessage = new Http::Message();
    brightnessMessage->addBodyText("{\"bri\":\"");
    brightnessMessage->addBodyText(newBrightness);
    brightnessMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    LightWidget::client->put(url, *brightnessMessage);

    currentLight->setBrightness(briSlider->value());

    generateLightInfo();

    delete brightnessMessage;
}

/**
 * setBrightness(unsigned int)
 *
 * Sets the brightness of the current light.
 * Used for themes.
 *
 * @param brightness
 */
void LightWidget::setBrightness(unsigned int brightness) {

    Http::Client *brightClient = new Wt::Http::Client(this);
    std::string newBrightness = std::to_string(brightness);

    Http::Message *brightnessMessage = new Http::Message();
    brightnessMessage->addBodyText("{\"bri\":\"");
    brightnessMessage->addBodyText(newBrightness);
    brightnessMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    brightClient->put(url, *brightnessMessage);

    currentLight->setBrightness(brightness);

    generateLightInfo();

    delete brightnessMessage;
}

/**
 * setHue()
 *
 * Sets the hue of the current light based on the slider value.
 */
void LightWidget::setHue() {

    std::string newHue = std::to_string(LightWidget::hueSlider->value());

    Http::Message *hueMessage = new Http::Message();
    hueMessage->addBodyText("{\"hue\":\"");
    hueMessage->addBodyText(newHue);
    hueMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    LightWidget::client->put(url, *hueMessage);

    currentLight->setHue(hueSlider->value());

    delete hueMessage;
}

/**
 * setHue(unsigned int)
 *
 * Sets the hue of the current light.
 * Used for themes.
 *
 * @param hue
 */
void LightWidget::setHue(unsigned int hue) {

    Http::Client *hueClient = new Wt::Http::Client(this);
    std::string newHue = std::to_string(hue);

    Http::Message *hueMessage = new Http::Message();
    hueMessage->addBodyText("{\"hue\":\"");
    hueMessage->addBodyText(newHue);
    hueMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    hueClient->put(url, *hueMessage);

    currentLight->setHue(hue);

    generateLightInfo();

    delete hueMessage;
}

/**
 * setSat()
 *
 * Sets the saturation of the current light based on the slider value.
 */
void LightWidget::setSat() {

    std::string newSat = std::to_string(LightWidget::satSlider->value());

    Http::Message *satMessage = new Http::Message();
    satMessage->addBodyText("{\"sat\":\"");
    satMessage->addBodyText(newSat);
    satMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    LightWidget::client->put(url, *satMessage);

    currentLight->setSaturation(satSlider->value());

    generateLightInfo();

    delete satMessage;
}

/**
 * setSat(unsigned int)
 *
 * Sets the saturation of the current light.
 * Used for themes.
 *
 * @param sat
 */
void LightWidget::setSat(unsigned int sat) {

    Http::Client *satClient = new Wt::Http::Client(this);
    std::string newSat = std::to_string(sat);

    Http::Message *satMessage = new Http::Message();
    satMessage->addBodyText("{\"sat\":\"");
    satMessage->addBodyText(newSat);
    satMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    satClient->put(url, *satMessage);

    currentLight->setSaturation(sat);

    generateLightInfo();

    delete satMessage;
}

/**
 * onOff()
 *
 * Toggles the light on and off.
 * Used by the on/off button.
 */
void LightWidget::onOff() {

    Http::Message *onOffMessage = new Http::Message();

    if (currentLight->getOn()) {
        onOffMessage->addBodyText("{\"on\":\"false\"}");
        currentLight->setOn(false);
        onOffButton->setText("Turn ON");
    }
    else {
        onOffMessage->addBodyText("{\"on\":\"true\"}");
        currentLight->setOn(true);
        onOffButton->setText("Turn OFF");
    }

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    LightWidget::client->put(url, *onOffMessage);

    delete onOffMessage;

}

/**
 * setOn(bool)
 *
 * Turns a light on or off.
 *
 * @param on true = on, false = off
 */
void LightWidget::setOn(bool on) {

    Http::Client *onClient = new Wt::Http::Client(this);
    Http::Message *onOffMessage = new Http::Message();

    if (currentLight->getOn()) {
        if (!on) {
            onOffMessage->addBodyText("{\"on\":\"false\"}");
            currentLight->setOn(false);
        }
    }
    else {
        if (on) {
            onOffMessage->addBodyText("{\"on\":\"true\"}");
            currentLight->setOn(true);
        }
    }

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    onClient->put(url, *onOffMessage);

}

/**
 * lightSelected()
 *
 * Responds to the user choosing a different light.
 */
void LightWidget::lightSelected() {
    currentLight = &lights[selectionBox->currentText().toUTF8()];

    if (currentLight->getOn()) {
        onOffButton->setText("Turn OFF");
    }
    else {
        onOffButton->setText("Turn ON");
    }

    briSlider->setValue(currentLight->getBrightness());
    hueSlider->setValue(currentLight->getHue());
    satSlider->setValue(currentLight->getSaturation());

    LightWidget::generateLightInfo();
}

/**
 * generateLightInfo()
 *
 * Updates the display of the light attributes.
 */
void LightWidget::generateLightInfo() {
    std::string s = "<p>Name: " + currentLight->getName() + "</p><p>Brightness: " + std::to_string(currentLight->getBrightness()) + "</p><p>Hue: " + std::to_string(currentLight->getHue()) + "</p><p>Saturation: " + std::to_string(currentLight->getSaturation()) + "</p>";
    lightInfoMessage->setText(s);
}

/**
 * changeTheme()
 *
 * Changes the current lights to a fun theme.
 */
void LightWidget::changeTheme() {

    if (group->checkedButton()->text().toUTF8() == "Christmas") {

        int count = 0;

        map<string, Light>::iterator it;

        for ( it = lights.begin(); it != lights.end(); it++ )
        {
            if ((count % 2) == 0) {
                currentLight = &(it->second);
                std::cout << "Current Light: " << currentLight->getName() << std::endl;
                setOn(true);
                setHue(0);      //red
                setBrightness(254);
                setSat(254);
            }
            else {
                currentLight = &(it->second);
                std::cout << "Current Light: " << currentLight->getName() << std::endl;
                setOn(true);
                setHue(25500);      //green
                setBrightness(254);
                setSat(254);
            }
            count++;
        }
    }
    else if (group->checkedButton()->text().toUTF8() == "Easter") {

        int count = 1;

        map<string, Light>::iterator it;

        for ( it = lights.begin(); it != lights.end(); it++ )
        {
            if (count == 1) {
                currentLight = &(it->second);
                std::cout << "Current Light: " << currentLight->getName() << std::endl;
                setOn(true);
                setHue(61166);      //pink
                setBrightness(254);
                setSat(127);
                count = 2;
            }
            else if (count == 2){
                currentLight = &(it->second);
                std::cout << "Current Light: " << currentLight->getName() << std::endl;
                setOn(true);
                setHue(44782);      //light purple-y blue
                setBrightness(254);
                setSat(127);
                count = 3;
            }
            else {
                currentLight = &(it->second);
                std::cout << "Current Light: " << currentLight->getName() << std::endl;
                setOn(true);
                setHue(25500);      //green
                setBrightness(254);
                setSat(127);
                count = 1;
            }
        }
    }
    else if (group->checkedButton()->text().toUTF8() == "Halloween") {

        int count = 0;

        map<string, Light>::iterator it;

        for ( it = lights.begin(); it != lights.end(); it++ )
        {
            if ((count % 2) == 0) {
                currentLight = &(it->second);
                std::cout << "Current Light: " << currentLight->getName() << std::endl;
                setOn(true);
                setHue(4733);      //orange
                setBrightness(254);
                setSat(254);
            }
            else {
                currentLight = &(it->second);
                std::cout << "Current Light: " << currentLight->getName() << std::endl;
                setOn(true);
                setHue(50972);      //dark purple
                setBrightness(254);
                setSat(254);
            }
            count++;
        }
    }

    generateLightInfo();

}
