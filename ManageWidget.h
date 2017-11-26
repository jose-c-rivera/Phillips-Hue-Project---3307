//
// Created by mike on 21/11/17.
//

#ifndef GROUP_MANAGEWIDGET_H
#define GROUP_MANAGEWIDGET_H

#include <Wt/WContainerWidget>

class ManageWidget: public Wt::WContainerWidget{
public:
    ManageWidget(const std::string username, Wt::WContainerWidget *parent = 0);
};


#endif //GROUP_ACCOUNTWIDGET_H