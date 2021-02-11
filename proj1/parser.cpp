


#include "DatumStack.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

string parseRString(std::istream &input);


// int main(){
//   string rstring = "1 { 4 2 / } / } } } ";
//   istringstream iss(rstring);
//   string p = parseRString(iss);
//   cout << p << endl;
//   return 0;
// }

std::string parseRString(std::istream &input){
  string rstring = "{";
  string var;
  int open_brackets = 0;
  int close_brackets = 0;
  while(close_brackets <= open_brackets){
    input >> var;
    if(var == "{"){
      rstring = rstring + " " + var;
      open_brackets++;
    }
    else if(var == "}"){
      rstring = rstring + " " + var;
      close_brackets++;
    }
    else{
      rstring = rstring + " " + var;
    }
  }
  return rstring;

}
