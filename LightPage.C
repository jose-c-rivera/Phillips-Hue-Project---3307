//Displays the account information

#include <vector>
#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include "LightPage.h"
#include "database.C"

using namespace std;
using namespace Wt;
extern string currentUser;

LightPage::LightPage(WContainerWidget *parent)
        : WContainerWidget(parent){



}


