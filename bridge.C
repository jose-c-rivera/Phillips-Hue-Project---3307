/*
 * File: bridge.C
 * Purpose: Class to represent a bridge
 * Language: C++
*/

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>

using namespace std;
namespace dbo = Wt::Dbo;

class Bridge{

public:
   string bridge_name;
   string location;
   string IP_Address;
   int port_num = 1000;
   string user_ID;

template<class Action>
   void persist(Action& a)
{
     dbo::field(a,bridge_name, "bridge_name");
     dbo::field(a,location, "location");
     dbo::field(a,IP_Address, "IP_Address");
     dbo::field(a,port_num, "port_num");
     dbo::field(a,user_ID, "user_ID");
}

string getBridgeName(){

   return bridge_name;

}

void setBridgeName(string input_name){

   bridge_name = input_name;

}

string getBridgeLocation(){

   return location;

}

void setBridgeLocation(string input_name){

   location = input_name;

}

string getIPAddress(){

   return IP_Address;

}

void setIPAddress(string IP_input){

   IP_Address = IP_input;

}

int getPortNum(){

   return port_num;

}

void setPortNum(int port){

   port_num = port;

}

};
