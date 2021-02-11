/* DatumStack.cpp
 * Written By: Daniel Plotkin
 * dplotk01
 * For: comp15
 * date: 2/19/20
 */

#include "DatumStack.h"

using namespace std;

DatumStack::DatumStack(){
  
}

DatumStack::DatumStack(Datum array[], int size){
  for(int i = 0; i < size; i++){
    datumStack.push_back(array[i]);
  }
}

bool DatumStack::isEmpty(){
  return datumStack.empty();
}

void DatumStack::clear(){
  datumStack.clear();
}

int DatumStack::size(){
  return datumStack.size();
}

Datum DatumStack::top(){
  if(datumStack.empty()){
    throw runtime_error("empty_stack");
  }
  else{
    return datumStack.back();
  }
}

void DatumStack::pop(){
  if(datumStack.empty()){
    throw runtime_error("empty_stack");
  }
  else{
    datumStack.pop_back();
  }
}

void DatumStack::push(Datum element){
  datumStack.push_back(element);
}
