#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_

#include "Datum.h"
#include <vector>
#include <fstream>
#include <iostream>

class DatumStack{
  public:
    //default constructor
    DatumStack();
    //constructor with an array and a size already defined
    DatumStack(Datum array[], int size);
    //returns true if the DatumStack is empty, otherwise false
    bool isEmpty();
    //clears the stack
    void clear();
    //returns the size of the stack
    int size();
    //returns the top of the stack, of type Datum
    Datum top();
    //removes the top element from the stack
    void pop();
    //adds an element to the top of the stack
    void push(Datum element);

  private:
    std::vector<Datum> datumStack;
};
#endif
