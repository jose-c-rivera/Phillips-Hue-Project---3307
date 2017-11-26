//
// Created by mike on 20/11/17.
//

#ifndef GROUP_HUEWIDGET_H
#define GROUP_HUEWIDGET_H

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <string>
//#include "session.C"

using namespace std;
namespace Wt{
    class WStackedWidget;
    class WAnchor;
}

class AccountWidget;
class ManageWidget;
class Database;

class hueWidget : public Wt::WContainerWidget{
public:
    hueWidget(Wt::WContainerWidget *parent = 0);
    string register_hash(Wt::WLineEdit* passEdit);
    void LogIn(Database* db, string email, string password);
    void handleInternalPath(const std::string &internalPath);
private:
    Wt::WStackedWidget *mainStack;
    AccountWidget *myAccount;
    ManageWidget *manage;
    Wt::WContainerWidget *nav;
    Wt::WAnchor *myAccountAnchor;
    //Wt::WAnchor *myBridgesAnchor;

    void showMyAccount();
    void showManage();
};

#endif //GROUP_HUEWIDGET_H
