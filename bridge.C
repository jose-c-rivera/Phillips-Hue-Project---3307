/**
 * @file    bridge.C
 * @Author  Jose Rivera <jrivera4@uwo.ca>
 * @date    Novemeber 2017
 * @brief   Class for bridge objects
 */
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <stdlib.h>
#include <string>

using namespace std;
namespace dbo = Wt::Dbo;

/**
 * @name: Bridge Constructor
 * @brief: Creates a bridge object
 * @return: Bridge Object
 */
class Bridge{

public:

   string bridge_name;
   string location;
   string IP_Address;
   string port_num;
   string user_ID;

/*
 * Template to map fields of object to database table
 */
template<class Action>
   void persist(Action& a)
{
     dbo::field(a,bridge_name, "bridge_name");
     dbo::field(a,location, "location");
     dbo::field(a,IP_Address, "IP_Address");
     dbo::field(a,port_num, "port_num");
     dbo::field(a,user_ID, "user_ID");
}

/**
 * @name: getBridgeName()
 * @brief: return the name of the bridge
 * @return: string 
 */
string getBridgeName(){

   return bridge_name;

}


/**
 * @name: setBridgeName(string input_name)
 * @param: The parmater will be the new name of the bridge
 * @brief: sets the name of the bridge
 * @return: string 
 */
void setBridgeName(string input_name){

   bridge_name = input_name;

}

/**
 * @name: getBridgeLocation()
 * @brief: return the name of the bridge's location
 * @return: string 
 */
string getBridgeLocation(){

   return location;

}

/**
 * @name: setBridgeLocation(string input_name)
 * @param: The paramater will be the new location of the bridge
 * @brief: sets the location of the bridge
 * @return: string 
 */
void setBridgeLocation(string input_name){

   location = input_name;

}

/**
 * @name: getIPAddress()
 * @brief: return the IP Address of the bridge
 * @return: string 
 */
string getIPAddress(){

   return IP_Address;

}

/**
 * @name: setIPAdress(string input_name)
 * @param: The paramater will be the new IP Address
 * @brief: sets the IP Address
 * @return: string 
 */
void setIPAddress(string IP_input){

   IP_Address = IP_input;

}

/**
 * @name: getPortNum()
 * @brief: return the port number
 * @return: string 
 */
string getPortNum(){

   return port_num;

}

/**
 * @name: setPortNum(string port)
 * @param: The parmater will be the new port number for the bridge
 * @brief: port number of the bridge
 * @return: string 
 */
void setPortNum(string port){

   port_num = port;

}

/**
 * @name: getUserID()
 * @return: string of user ID
 * @brief: returns User ID for the bridge
 */
string getUserID(){
   return user_ID;
}

/**
 * @name: setUserID()
 * @param: The parmater will be the new ID for the bridge
 * @brief: User ID for the bridge
 */
void setUserID(string id){

   user_ID = id;
}
};
