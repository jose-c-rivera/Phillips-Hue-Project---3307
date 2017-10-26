#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WImage>
#include <Wt/WCssDecorationStyle>
#include <Wt/WColor>

// c++0x only, for std::bind
// #include <functional>

using namespace Wt;


class HueProject : public WApplication
{
public:
  HueProject(const WEnvironment& env);

private:
  WText *greeting_;

  void greet();
};

HueProject::HueProject(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Hue Project - Team 9");                               // application title

  WCssDecorationStyle *menu = new WCssDecorationStyle();
  menu->setBackgroundImage("https://www.xmple.com/wallpaper/black-purple-gradient-linear-1920x1080-c2-000000-9370db-a-105-f-14.svg");

  root()->addWidget(new WText("Hue Project - Team 09"));  // show some text

}

WApplication *createApplication(const WEnvironment& env)
{
  return new HueProject(env);
}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}

