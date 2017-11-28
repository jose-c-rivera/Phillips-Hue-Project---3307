/**
 * LightWidget.C
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

#include "LightWidget.h"

using namespace Wt;

LightWidget::LightWidget(WContainerWidget *parent)
        : WContainerWidget(parent){

    layout = new Wt::WGridLayout();

    //CSS
    addStyleClass("account_container");

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

            std::cout << "ITERATION " << light << std::endl;

            if (result.contains(light)) {
                std::cout << "RESULT CONTAINS " << light << std::endl;
                std::cout << "RESULT TYPE: " << result.type(light) << std::endl;
                Json::Object tempObject = result.get(light);
                if (tempObject.contains("name")) {
                    std::cout << "TEMP_OBJECT CONTAINS name" << std::endl;
                    std::cout << "TEMP_OBJECT TYPE: " << tempObject.type("name") << std::endl;
                    std::string s = tempObject.get("name");
                    std::cout << s << std::endl;
                }
                else {
                    std::cout << "TEMP_OBJECT DOES NOT CONTAIN name" << std::endl;
                }
            }
            else {
                std::cout << "RESULT DOES NOT CONTAIN 1" << std::endl;
            }

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

void LightWidget::setBrightness() {

    std::string newBrightness = std::to_string(LightWidget::briSlider->value());

    Http::Message *brightnessMessage = new Http::Message();
    brightnessMessage->addBodyText("{\"bri\":\"");
    brightnessMessage->addBodyText(newBrightness);
    brightnessMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    LightWidget::client->put(url, *brightnessMessage);

    currentLight->setBrightness(briSlider->value());

    delete brightnessMessage;
}

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

void LightWidget::setSat() {

    std::string newSat = std::to_string(LightWidget::satSlider->value());

    Http::Message *satMessage = new Http::Message();
    satMessage->addBodyText("{\"sat\":\"");
    satMessage->addBodyText(newSat);
    satMessage->addBodyText("\"}");

    std::string url = "http://localhost:8000/api/newdeveloper/lights/" + currentLight->getID() + "/state";

    LightWidget::client->put(url, *satMessage);

    currentLight->setSaturation(satSlider->value());

    delete satMessage;
}

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

void LightWidget::generateLightInfo() {
    std::string s = "<p>Name: " + currentLight->getName() + "</p><p>Brightness: " + std::to_string(currentLight->getBrightness()) + "</p>";
    lightInfoMessage->setText(s);
}