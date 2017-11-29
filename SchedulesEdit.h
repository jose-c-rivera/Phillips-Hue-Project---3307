/**
 * @file SchedulesEdit.h
 * @Author: Allan Khan
 * @date: November 2017
 * @brief Header for SchedulesEdit.C
 */

#ifndef GROUP_SCHEDULESEDIT_H
#define GROUP_SCHEDULESEDIT_H

#include <Wt/WLineEdit>
#include <Wt/WContainerWidget>
#include <Wt/WSlider>
#include <Wt/WRadioButton>
#include <Wt/WButtonGroup>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/Http/Client>

using namespace Wt;

class SchedulesEdit: public Wt::WContainerWidget{
	public:
		SchedulesEdit(Wt::WContainerWidget *parent = 0);
	private:
		//Prototypes
		Http::Client *client = new Http::Client(this);
		WRadioButton *buttonA;
		WButtonGroup *group = new WButtonGroup(this);
		WSlider *briSlider = new WSlider(Wt::Vertical);
		WSlider *hueSlider = new WSlider(Wt::Vertical);
		WSlider *satSlider = new WSlider(Wt::Vertical);
		WLineEdit *IDNum;
		WText *IDtext;
		WLineEdit *schedName;
		WLineEdit *schedDesc;
		WLineEdit *date;
		WLineEdit *time;
		WText *blank;
	//Function prototypes
	void setSchedule();		
};

#endif
