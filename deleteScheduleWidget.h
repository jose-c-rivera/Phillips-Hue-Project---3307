#ifndef GROUP_DELETESCHEDULEWIDGET_H
#define GROUP_DELETESCHEDULEWIDGET_H

#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/WGridLayout>

class DeleteScheduleWidget: public Wt::WContainerWidget{
public:
	DeleteScheduleWidget(Wt::WContainerWidget *parent = 0);
private:
	Wt::WLineEdit *deleteAtID;
	Wt::WText *deleteText;
	Wt::Http::Client *client;
	void delSchedule();
	
};
#endif
