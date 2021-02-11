

#include "DatumStack.h"
using namespace std;


int main(){
  Datum list[3] = {Datum(6), Datum(true), Datum("string")};
  DatumStack d = DatumStack(list, 3);
  while(true){
    cout << "What do you want to do?" << endl;
    string choice;
    cin >> choice;
    if(choice == "top"){
      Datum top = d.top();
      cout << top.toString() << endl;
    }
    else if(choice == "pop"){
      d.pop();
    }
    else if(choice == "isEmpty"){
      bool t = d.isEmpty();
      cout << t << endl;
    }
    else if(choice == "size"){
      int size = d.size();
      cout << size << endl;
    }
    else if(choice == "clear"){
      d.clear();
    }
    else if(choice == "push"){
      d.push(Datum(6));
    }
    else if(choice == "stop"){
      break;
    }
  }
  return 0;
}
