//
// Created by mike on 21/11/17.
//

#ifndef GROUP_LIGHTPAGE_H
#define GROUP_LIGHTPAGE_H

#include <Wt/WContainerWidget>

class Light;
class LightWidget;

class LightPage: public Wt::WContainerWidget{
public:
    LightPage(Wt::WContainerWidget *parent = 0);

private:
	LightWidget *lighttest;
};


#endif //GROUP_LIGHTPAGE_H