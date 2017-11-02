/*
 * File: passEncrypt.h
 * Purpose: Contains methods to hash passwords, and compare them to stored
 *          values in a database.
 * Language: C++
*/

#include <math.h>
#include <stdlib.h>
#include <string>

using namespace std;

string tempPass;

string hashPass(string input_string);
int comparePass(string input_string, string stored_string);

//This site will help with manipulating a string in C++ : https://cal-linux.com/tutorials/strings.html
string hashPass(string input_string){
/*
Implementation will go here
*/
  return "test phrase";
}


int comparePass(string input_string, string stored_string){

/*
Implementation should take as input, whatever string the user 
inputted after it was hashed, and then compare it 
to the hashed string in the database. RETURN 1 if 
a match and RETURN 0 if not a match.
*/
  return 1;
}
