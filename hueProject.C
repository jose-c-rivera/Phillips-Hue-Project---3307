#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WImage>
#include <Wt/WCssDecorationStyle>
#include <Wt/WColor>
#include "userAccount.C"

// c++0x only, for std::bind
// #include <functional>

using namespace Wt;


class HueProject : public WApplication
{
public:
  HueProject(const WEnvironment& env);

private:
  WLineEdit *nameEdit_;
  WText *greeting_;

  void greet();
};

HueProject::HueProject(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Hue Project - Team 9");                               // application title

  WCssDecorationStyle* menu = new WCssDecorationStyle();
 // menu->setBackgroundImage("https://www.xmple.com/wallpaper/black-purple-gradient-linear-1920x1080-c2-000000-9370db-a-105-f-14.svg");

  root()->addWidget(new WText("Please enter your first name:"));  // show some text

  //root()->addWidget(std:make_unique<Wt::WBreak>());
  //nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
  

  User_Account* trial = new User_Account;
  trial->setFirstName("Jose");
  trial->setLastName("Rivera");
  root()->addWidget(new WText("Hi, this is " + trial->getFirstName() + " " + trial->getLastName() ));


}

WApplication *createApplication(const WEnvironment& env)
{
  return new HueProject(env);
}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}

