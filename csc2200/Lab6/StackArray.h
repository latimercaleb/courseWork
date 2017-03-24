//--------------------------------------------------------------------
//
//  Laboratory 6                                         StackLinked.h
// 
//  Class declaration for the linked implementation of the Stack ADT
//
//--------------------------------------------------------------------

#ifndef STACKARRAY_H
#define STACKARRAY_H

#include <stdexcept>
#include <iostream>

using namespace std;

#include "Stack.h"

template <typename DataType>
class StackArray : public Stack<DataType> {
  public:
    StackArray(int maxNumber = Stack<DataType>::MAX_STACK_SIZE);
    StackArray(const StackArray& other);
    StackArray& operator=(const StackArray& other);
    ~StackArray();

    void push(const DataType& newDataItem) throw (logic_error);
    DataType pop() throw (logic_error);

    void clear();

    bool isEmpty() const;
    bool isFull() const;

    void showStructure() const;

  private:
    int maxSize;
    int top;
    DataType* dataItems;
};

#endif		//#ifndef STACKARRAY_H
