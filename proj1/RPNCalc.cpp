/* RPNCalc.cpp
 * Written By: Daniel Plotkin
 * dplotk01
 * For: comp15
 * date: 2/19/20
 */

 #include "RPNCalc.h"
 #include "DatumStack.h"
 #include "Datum.h"

 using namespace std;

//  RPNCalc::RPNCalc(){
//    stack = {};
//  }
//
// RPNCalc::~RPNCalc(){
//   delete[] stack;
// }

/*
  the main driver of the program
  when called, runs the input loop, allowing a user to input
  various commands or an input file
 */
 void RPNCalc::run(){
   while (true){
     string input;
     int value;
     cin >> input;
     if (input == "#t"){
       Datum true_d = Datum(true);
       stack.push(true_d);
     }
     else if(got_int(input, &value)){
       stack.push(value);
     }
     else if (input == "#f"){
       Datum false_d = Datum(false);
       stack.push(false_d);
     }
     else if (input == "print"){
       print_top();
     }
     else if(input == "not"){
       not_command();
     }
     else if (input == "quit"){
       cerr << "Thank you for using CalcYouLater.\n";
       break;
     }
     else if (cin.eof()){
       cerr << "Thank you for using CalcYouLater\n";
       break;
     }
     else if (input == "clear"){
       stack.clear();
     }
     else if (input == "drop"){
       drop();
     }
     else if (input == "dup"){
       dup();
     }
     else if (input == "swap"){
       swap();
     }
     else if(input == "*" || input == "/" || input == "+" || input == "-" ||
             input == "mod"){
              do_math(input);
            }
    else if(input == "<" || input == ">" || input == "<=" || input == ">=" ||
            input == "=="){
              compare(input);
            }
    else if(input == "{"){
      Datum rstring = parseRString(cin);
      stack.push(rstring);
    }
    else if(input == "exec"){
      exec();
    }
    else if(input == "file"){
      file();
    }
    else if(input == "if"){
      if_command();
    }
    else{
      if(input != ""){
        cerr << input << ": unimplemented\n";
      }
    }
   }
 }


 bool RPNCalc::got_int(string s, int *resultp)
 {
         return sscanf(s.c_str(), "%d", resultp) == 1;
 }

/*
  performs a given arithmetic operation
  on the top 2 elements of the datumStack
  if one of the elements is not an integer, gives an error
*/
void RPNCalc::do_math(string op){
  Datum b = stack.top();
  stack.pop();
  if(stack.isEmpty()){
    cerr << "Error: empty_stack" << endl;
  }
  else{
    Datum a = stack.top();
    stack.pop();
    if(!a.isInt() || !b.isInt()){
      cerr << "Error: datum_not_int\n";
      stack.push(a);
      stack.push(b);
    }
    else{
      int a_int = a.getInt();
      int b_int = b.getInt();
      if(op == "*"){
        int c = a_int * b_int;
        Datum out = Datum(c);
        stack.push(c);
      }
      else if(op == "/"){
        if(b_int == 0){
          cerr << "divide by zero\n";
        }
        else{
          int c = a_int / b_int;
          Datum out = Datum(c);
          stack.push(c);
        }
      }
      else if(op == "+"){
        int c = a_int + b_int;
        Datum out = Datum(c);
        stack.push(c);
      }
      else if(op == "-"){
        int c = a_int - b_int;
        Datum out = Datum(c);
        stack.push(c);
      }
      else if(op == "mod"){
        int c = a_int % b_int;
        Datum out = Datum(c);
        stack.push(c);
      }
    }
  }
}

/*
    runs a comparison operator on the top 2 elements of the datumStack
    if one of these is not an int, prints an error
 */
void RPNCalc::compare(string op){
  Datum b = stack.top();
  stack.pop();
  if(stack.isEmpty()){
    cerr << "Error: empty_stack\n";
  }
  else{
    Datum a = stack.top();
    stack.pop();
    if(!a.isInt() || !b.isInt()){
      cerr << "Error: datum_not_int\n";
      stack.push(a);
      stack.push(b);
    }
    else{
      int a_int = a.getInt();
      int b_int = b.getInt();
      if(op == "<"){
        bool c = a_int < b_int;
        if(c){
          Datum d = Datum(true);
          stack.push(d);
        }
        else{
          Datum d = Datum(false);
          stack.push(d);
        }
      }
      else if(op == ">"){
          bool c = a_int > b_int;
          if(c){
            Datum d = Datum(true);
            stack.push(d);
          }
          else{
            Datum d = Datum(false);
            stack.push(d);
          }
      }
      else if(op == "<="){
        bool c = a_int <= b_int;
        if(c){
          Datum d = Datum(true);
          stack.push(d);
        }
        else{
          Datum d = Datum(false);
          stack.push(d);
        }
      }
      else if(op == ">="){
        bool c = a_int >= b_int;
        if(c){
          Datum d = Datum(true);
          stack.push(d);
        }
        else{
          Datum d = Datum(false);
          stack.push(d);
        }
      }
      else if(op == "=="){
        bool c = a_int == b_int;
        if(c){
          Datum d = Datum(true);
          stack.push(d);
        }
        else{
          Datum d = Datum(false);
          stack.push(d);
        }
      }
    }
  }
}

/*
  parses an rString and returns it
*/
string RPNCalc::parseRString(istream &input){
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

/*
 executes the commands inside of the top of the stack, an rstring
 if the top element is not an rstring, prints an error
*/
void RPNCalc::exec(){
  Datum rstring = stack.top();
  if(!rstring.isRString()){
    cerr << "Error: cannot execute non rstring\n";
  }
  else{
    stack.pop();
    string new_string = rstring.getRString();
    istringstream iss(new_string);
    string input;
    int open_brackets = 1;
    int close_brackets = 0;
    int value;
    iss >> input;
    while(close_brackets < open_brackets){
      iss >> input;
        if (input == "#t"){
          Datum true_d = Datum(true);
          stack.push(true_d);
        }
        else if(input == "}"){
          close_brackets++;
        }
        else if(got_int(input, &value)){
          stack.push(value);
        }
        else if (input == "#f"){
          Datum false_d = Datum(false);
          stack.push(false_d);
        }
        else if (input == "print"){
          print_top();
        }
        else if(input == "not"){
          not_command();
        }
        else if (input == "quit"){
          cerr << "Thank you for using CalcYouLater.\n";
          break;
        }
        else if (input == "clear"){
          stack.clear();
        }
        else if (input == "drop"){
          drop();
        }
        else if (input == "dup"){
          dup();
        }
        else if (input == "swap"){
          swap();
        }
        else if(input == "*" || input == "/" || input == "+" || input == "-" ||
                input == "mod"){
                 do_math(input);
               }
       else if(input == "<" || input == ">" || input == "<=" || input == ">=" ||
               input == "=="){
                 compare(input);
               }
       else if(input == "{"){
         Datum rstring = parseRString(iss);
         stack.push(rstring);
       }
       else if(input == "if"){
         if_command();
       }
       else if(input == "exec"){
         exec();
       }
       else if(input == "file"){
         file();
       }
       else{
         if(input != ""){
           cerr << input << ": unimplemented\n";
         }

       }
    }
  }
}

/*
  opens a file inside of an rstring and runs the commands inside the file
*/
void RPNCalc::file(){
  Datum top = stack.top();
  int value;
  if(!top.isRString()){
    cerr << "Error: file operand not rstring\n";
  }
  else{
    stack.pop();
    string rstring = top.getRString();
    istringstream iss (rstring);
    string file;
    iss >> file;
    iss >> file;
    ifstream infile(file.c_str());
    if(infile.fail()){
      cerr << "Unable to read " << file << endl;
      return;
    }
    while (!infile.eof()){
      string command;
      infile >> command;
      if (command == "#t"){
        Datum true_d = Datum(true);
        stack.push(true_d);
      }
      else if(got_int(command, &value)){
        stack.push(value);
      }
      else if (command == "#f"){
        Datum false_d = Datum(false);
        stack.push(false_d);
      }
      else if (command == "print"){
        print_top();
      }
      else if (command == "quit"){
        cerr << "Thank you for using CalcYouLater.\n";
        break;
      }
      else if (command == "clear"){
        stack.clear();
      }
      else if (command == "drop"){
        drop();
      }
      else if(command == "not"){
        not_command();
      }
      else if (command == "dup"){
        dup();
      }
      else if (command == "swap"){
        swap();
      }
      else if(command == "*" || command == "/" || command == "+" ||
            command == "-" || command == "mod"){
               do_math(command);
             }
     else if(command == "<" || command == ">" || command == "<=" ||
            command == ">=" || command == "=="){
               compare(command);
             }
     else if(command == "{"){
       Datum rstring = parseRString(infile);
       stack.push(rstring);
     }
     else if(command == "exec"){
       exec();
     }
     else if(command == "if"){
       if_command();
     }
     else{
       if(command != ""){
         cerr << command << ": unimplemented\n";
       }
     }
    }
  }
}

/*
  takes the top 3 elements on the stack, in the order of rstring, rstring, bool
  if the bool is true, exec the top element of the stack
  if the bool is false, exec the second element of the stack
*/
void RPNCalc::if_command(){
  Datum first_input = stack.top();
  stack.pop();
  Datum second_input = stack.top();
  stack.pop();
  Datum comparator = stack.top();
  stack.pop();
  if(!first_input.isRString() || !second_input.isRString()){
    cerr << "Error: expected rstring in if branch\n";
  }
  else if(comparator.toString() != "#t" && comparator.toString() != "#f"){
    cerr << "Error: expected boolean in if test\n";
  }
  else{
    if(comparator.toString() == "#f"){
      stack.push(first_input);
      exec();
    }
    else{
      stack.push(second_input);
      exec();
    }
  }
}

/*
  removes the top element from the datumStack
*/
void RPNCalc::drop(){
  if(stack.isEmpty()){
    cerr << "Error: empty_stack\n";
  }
  else{
    stack.pop();
  }
}

//prints the top element of the stack
void RPNCalc::print_top(){
  if(stack.isEmpty()){
    cerr << "Error: empty_stack\n";
  }
  else{
    Datum top = stack.top();
    cout << top.toString() << endl;
  }
}

//duplicates the top element of the stack

void RPNCalc::dup(){
  if(stack.isEmpty()){
     cerr << "Error: empty_stack\n";
  }
  else{
    Datum top = stack.top();
    stack.push(top);
  }
}

// swaps the top two elements of the stack

void RPNCalc::swap(){
  if(stack.isEmpty()){
    cerr << "Error: empty_stack\n";
  }
  else{
    Datum top = stack.top();
    stack.pop();
    Datum second = stack.top();
    stack.push(top);
    stack.push(second);
  }
}

void RPNCalc::not_command(){
  if(stack.isEmpty()){
    cerr << "Error: empty_stack\n";
  }
  else if(!stack.top().isBool()){
    cerr << "Error: datum_not_bool\n";
  }
  else{
    Datum top = stack.top();
    stack.pop();
    if(top.toString() == "#t"){
      Datum opposite = Datum(false);
      stack.push(opposite);
    }
    else{
      Datum opposite = Datum(true);
      stack.push(opposite);
    }
  }
}
