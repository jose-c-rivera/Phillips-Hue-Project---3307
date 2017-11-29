//
// Created by mike on 20/11/17.
//

#ifndef GROUP_HUEWIDGET_H
#define GROUP_HUEWIDGET_H

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <string>
#include <Wt/WText>

using namespace std;
namespace Wt{
    class WStackedWidget;
    class WAnchor;
}

class AccountWidget;
class ManageWidget;
class LightPage;
class Database;
class BridgeEdit;
class SchedulesWidget;

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
    LightPage *lights;
    BridgeEdit *bridgeedit;
    SchedulesWidget *schedules;
    WContainerWidget *content;
    WContainerWidget *nav_main;
    Wt::WText *loginState;
    Wt::WPushButton *logoutButton;
    Wt::WContainerWidget *nav;
    Wt::WAnchor *myAccountAnchor;
    //Wt::WAnchor *myBridgesAnchor;

    void showMyAccount();
    void showManage();
    void showLogin();
    void showNav();
    void logout();
    void showLights();
    void showBridgeEdit();
    void showSchedules();
};

#endif //GROUP_HUEWIDGET_H
