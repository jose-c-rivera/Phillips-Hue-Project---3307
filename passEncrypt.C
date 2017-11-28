/**
 * @file    passEncrypt.C
 * @Author  Fran Plancke <fplancke@uwo.ca>
 * @date    Novemeber 2017
 * @brief   Class for encypting and comparing strings
 */
#include <stdlib.h>
#include <string>
#include <iostream>
#include <functional>
using namespace std;

/**
 * @name: passEncrypt()
 * @brief: Creates a passEncrypt object
 */
class passEncrypt{

public:
string tempPass;

passEncrypt() {
    cout << "passEncrypt constructor called" << endl;
}

/**
 * @name: setTemp()
 * @param: string to set as the new temporary string
 * @brief: Sets the temp string belonging to the object
 */
void setTemp(string temp){
   tempPass = temp;
}

/**
 * @name: getTemp()
 * @return: tempPass
 * @brief: Returns value of tempPass belonging to passEncrypt
 */
string getTemp(){
   return tempPass;
}

/**
 * @name: hashPass()
 * @param: Accepts a string to hash
 * @return: The hashed string
 * @brief: Accepts a string from the user and returns the hash of that string
 */
string hashPass(string input_string){
    hash<string> string_hash;
 
    cout << "hashPass() called. Returning " << string_hash(input_string) << endl;
    return to_string(string_hash(input_string));
}

/**
 * @name: comparePass()
 * @param: Accepts 2 strings
 * @return: 1 of strings match and 0 if they dont
 * @brief: Compares 2 inout strings and returns value to indicate result
 */
int comparePass(string input_string, string stored_string){

    hash<string> string_hash;
    
    if(string_hash(input_string) == string_hash(stored_string)){
        cout << "Passwords match" << endl;
        return 1;
    }
    else{
        cout << "Passwords didn't match" << endl;
        return 0;
    }
}
};
