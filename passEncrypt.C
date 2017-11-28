/**
 * @file    passEncrypt.C
 * @Author  Fran Plancke 
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

void setTemp(string temp){
   tempPass = temp;
}

string getTemp(){
   return tempPass;
}

string hashPass(string input_string){
    hash<string> string_hash;
 
    cout << "hashPass() called. Returning " << string_hash(input_string) << endl;
    return to_string(string_hash(input_string));
}

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
