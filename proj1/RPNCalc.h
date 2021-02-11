#ifndef _RPNCALC_H_
#define _RPNCALC_H_

#include "DatumStack.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

class RPNCalc{

public:
  //default constructor
  // RPNCalc();
  // //destructor
  // ~RPNCalc();
  //runs the program
  void run();

private:
  void print_top();
  void drop();
  void swap();
  void dup();
  DatumStack stack;
  bool got_int(std::string s, int *resultp);
  void do_math(std::string op);
  void compare(std::string op);
  std::string parseRString(std::istream &input);
  void exec();
  void file();
  void if_command();
  void not_command();


};
#endif
