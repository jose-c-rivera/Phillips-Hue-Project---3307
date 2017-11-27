/*
 * Filename: hueProject.C
 * Purpose: Main file where our application switches views for the user
 * Langauge: C++
 */
#include <Wt/WApplication>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/WServer>
#include "hueWidget.h"

using namespace Wt;

WApplication *createApplication(const WEnvironment& env)
{
    WApplication *hue = new WApplication(env);
    
    hue->useStyleSheet("css/main.css");
    hue->setTitle("Hue Project - Team 9");

    new hueWidget(hue->root());

    return hue;
}

////////////////////////////////////////////////MAIN APP//////////////////////////////////////////


int main(int argc, char **argv)
{
    WServer server(argc, argv, WTHTTP_CONFIGURATION);
    server.addEntryPoint(Application, createApplication);
    server.run();
}

