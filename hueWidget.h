//
// Created by mike on 20/11/17.
//

#ifndef GROUP_HUEWIDGET_H
#define GROUP_HUEWIDGET_H

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <string>

using namespace std;
namespace Wt{
    class WStackedWidget;
    class WAnchor;
}

class AccountWidget;
class TestWidget;

class hueWidget : public Wt::WContainerWidget{
public:
    hueWidget(Wt::WContainerWidget *parent = 0);
    string register_insert(Wt::WLineEdit* passEdit);
    void handleInternalPath(const std::string &internalPath);
    void showMyTest();

private:
    Wt::WStackedWidget *mainStack;
    AccountWidget *myAccount;
    TestWidget *myTest;
    Wt::WContainerWidget *nav;
    Wt::WAnchor *myAccountAnchor;
    //Wt::WAnchor *myBridgesAnchor;

    void showMyAccount();
    //void showMyBridges();
};

#endif //GROUP_HUEWIDGET_H
