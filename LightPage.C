/**
 * LightPage.C
 *
 * Author: Fran Plancke, Mike Davis
 *
 * Implementation file for LightWidget.
 *
 * The LightWidget class allows the user to view and modify light elements.
 */

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
#include "Light.C"
#include "LightWidget.C"

using namespace std;
using namespace Wt;
extern string currentUser;

LightPage::LightPage(WContainerWidget *parent): 
	WContainerWidget(parent),
	lighttest(0)
{
	addStyleClass("lightPage");
    lighttest = new LightWidget();
    addWidget(lighttest);

}


