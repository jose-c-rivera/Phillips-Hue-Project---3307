#ifndef GROUP_SCHEDULESWIDGET_H
#define GROUP_SCHEDULESWIDGET_H

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WContainerWidget>
#include <Wt/Http/Client>
#include <Wt/WSlider>
#include <Wt/WPushButton>
#include <Wt/WRadioButton>
#include <Wt/WButtonGroup>

using namespace Wt;

class DeleteScheduleWidget;
class SchedulesEdit;

class SchedulesWidget: public Wt::WContainerWidget{
	public:
		SchedulesWidget(Wt::WContainerWidget *parent = 0);
	private:
		Http::Client *client = new Http::Client(this);
		WRadioButton *buttonA;
		WButtonGroup *group = new WButtonGroup(this);
		WButtonGroup *groupB = new WButtonGroup(this);
		WButtonGroup *groupC = new WButtonGroup(this);
		WButtonGroup *groupD = new WButtonGroup(this);
		WSlider *briSlider = new WSlider(Wt::Vertical);
		WSlider *hueSlider = new WSlider(Wt::Vertical);
		WSlider *satSlider = new WSlider(Wt::Vertical);
		WLineEdit *groups_or_lights;
		WLineEdit *IDNum;
		WText *IDtext;
		WLineEdit *schedName;
		WLineEdit *schedDesc;
		WLineEdit *date;
		WLineEdit *time;
		WLineEdit *bri;
		WLineEdit *hue;
		DeleteScheduleWidget *deleteSchedule;
		SchedulesEdit *editSchedule;
		WText *blank;
	void schedule_SET();
	//void handleHttpResponse(boost::system::error_code err, const Http::Message& response);		
};

#endif

