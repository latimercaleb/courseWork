//--------------------------------------------------------------------
//
//  Laboratory 6                                       StackLinked.cpp
//
//--------------------------------------------------------------------

#ifndef STACKLINKED_CPP
#define STACKLINKED_CPP

#include <iostream>

#include "StackLinked.h"


//--------------------------------------------------------------------

template <typename DataType>
StackLinked<DataType>::StackLinked(int maxNumber): top(NULL)
 
// Creates an empty stack. The parameter maxNumber is provided for 
// compatability with the array implementation and is ignored.

{
	
}

//--------------------------------------------------------------------

template <typename DataType>
StackLinked<DataType>::StackLinked(const StackLinked& other)

// Copy constructor for linked stack

{
	if (this != &other) {
		this = other;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
StackLinked<DataType>& StackLinked<DataType>::operator=(const StackLinked& other)

// Overloaded assignment operator for the StackLinked class.
// Because this function returns a StackLinked object reference,
// it allows chained assignment (e.g., stack1 = stack2 = stack3).

{
	StackNode temp = new StackNode(other.dataItem, other.next);
	while (other->next != NULL) {
		temp->next = other->next;
	}
	return temp;
}

//--------------------------------------------------------------------

template <typename DataType>
StackLinked<DataType>::~StackLinked() 

// Destructor. Frees the memory used by a stack.

{
	delete top; // maybe need to change? 
}

//--------------------------------------------------------------------

template <typename DataType>
void StackLinked<DataType>::push(const DataType& newDataItem) throw (logic_error) 

// Inserts newDataItem onto the top of a stack.

{
	if (top == NULL) {
		StackNode *head = new StackNode(newDataItem, NULL);
		top = head;
	}
	else {
		StackNode *next = new StackNode(newDataItem, top);
		top = next;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
DataType StackLinked<DataType>::pop() throw (logic_error) 

// Removes the topmost item from a stack and returns it.

{
	if (isEmpty()) {
		throw logic_error("List is already empty!!");
	}
	else {
		DataType temp = top->dataItem;
		StackNode *tempNode;
		tempNode = top;
		top = top->next;
		delete tempNode;
		return temp;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
void StackLinked<DataType>::clear() 

// Removes all the data items from a stack.

{
	while (!isEmpty()) {
		pop();
	}
}

//--------------------------------------------------------------------

template <typename DataType>
bool StackLinked<DataType>::isEmpty() const 

// Returns true if a stack is empty. Otherwise, returns false.

{
	if (top == NULL) {
		return true;
	}
	else if (top < 0) {
		return true;
	}
    return false;
}

//--------------------------------------------------------------------

template <typename DataType>
bool StackLinked<DataType>::isFull() const 

// Returns true if a stack is full. Otherwise, returns false. 

{
    return false; // linked list can never be full so returns false
}

//--------------------------------------------------------------------

template <typename DataType>
void StackLinked<DataType>::showStructure() const 

// Linked list implementation. Outputs the data elements in a stack.
// If the stack is empty, outputs "Empty stack". This operation is
// intended for testing and debugging purposes only.

{
    if( isEmpty() )
    {
	cout << "Empty stack" << endl;
    }
    else
    {
        cout << "Top\t";
	for (StackNode* temp = top; temp != 0; temp = temp->next) {
	    if( temp == top ) {
		cout << '[' << temp->dataItem << "]\t";
	    }
	    else {
		cout << temp->dataItem << "\t";
	    }
	}
        cout << "Bottom" << endl;
    }
}

#endif		//#ifndef STACKLINKED_CPP
