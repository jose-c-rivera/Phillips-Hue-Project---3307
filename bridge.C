/*
 * File: bridge.C
 * Purpose: Class to represent a bridge
 * Language: C++
*/

#include <string>

using namespace std;

class Bridge{

private:
   string bridge_name = "[undefined]";
   string location = "[undefined]";
   string IP_Address = "[undefined]";
   int port_num = 1000;

public:

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
