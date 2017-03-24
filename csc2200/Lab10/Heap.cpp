//--------------------------------------------------------------------
//
//  Laboratory 11                                            Heap.cpp
//
//  
//
//--------------------------------------------------------------------
#ifndef HEAP_CPP
#define HEAP_CPP
#include "Heap.h"
//#include <new>
using namespace std;
//--------------------------------------------------------------------
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>:: Heap ( int maxNumber )
// Creates an empty heap. Allocates enough memory for maxNumber
// data items.

  : maxSize(maxNumber),
    size(0)
{
    dataItems = new DataType [ maxSize ];
}

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>:: Heap ( const Heap& other )

// Copy constructor

  /*: maxSize(other.maxSize),
    size(other.size)*/
{
	if (this != &other) {
		*this = other;
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>& Heap<DataType,KeyType,Comparator>:: operator= ( const Heap& other )

{
    
	maxSize = other.maxSize;
	size = other.size;
	dataItems = new DataType[maxSize];
	for (int i = 0; i < other.maxSize; i++) {
		dataItems[i] = other.dataItems[i];
	}
	return *this;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>:: ~Heap ()

// Frees the memory used by a heap.

{
	clear();
	delete[] dataItems; // destroy dataItems 
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: insert ( const DataType &newDataItem ) throw ( logic_error )

// Inserts newDataItem into a heap. This data item is initially
// inserted as the bottom rightmost data item in the heap. It is then
// moved upward until a valid heap is produced.

{
	if (isFull()) {
		throw("Cannot insert into a full heap!!");
	}
	else {
		int index = size;
		Comparator compare;
		dataItems[size] = newDataItem;
		while (compare(dataItems[index].getPriority(),dataItems[(index - 1) / 2].getPriority())){
			DataType datasubstitute = dataItems[index];
			dataItems[index] = dataItems[(index - 1) / 2];
			dataItems[(index - 1) / 2] = datasubstitute;
			index = (index - 1) / 2;
		}
		size++;
	}

}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType,KeyType,Comparator>:: remove () throw ( logic_error )

// Removes the data item with the highest priority (the root) from a
// heap and returns it. This data item is replaced with the bottom
// rightmost data item, which is moved downward until a valid heap is
// produced.

{
	if (isEmpty()) {
		throw logic_error(" Cannot remove from an empty heap!!");
	}
	else {
		DataType oldMax = dataItems[0];    // Data item removed (old root)
		size--; 
		dataItems[0] = dataItems[size];
		int index = 0;
		while (index < size){
			Comparator compare;
			if ((index * 2) + 2 <= size)
			{
				if (compare(dataItems[index].getPriority(),
					dataItems[(index * 2) + 1].getPriority()) &&
					compare(dataItems[index].getPriority(),
						dataItems[(index * 2) + 2].getPriority())){
					return oldMax;
				}
				else if (compare(dataItems[(index * 2) + 2].getPriority(),dataItems[(index * 2) + 1].getPriority())){
					DataType temp = dataItems[index];
					dataItems[index] = dataItems[(index * 2) + 2];
					dataItems[(index * 2) + 2] = temp;
					index = (index * 2) + 2;
				}
				else{
					DataType temp = dataItems[index];
					dataItems[index] = dataItems[index + 1];
					dataItems[(index * 2) + 1] = temp;
					index = (index * 2) + 1;
				}
			}
			else if ((index * 2) + 1 <= size){
				if (compare(dataItems[(index * 2) + 1].getPriority(),dataItems[index].getPriority())){
					DataType temp = dataItems[index];
					dataItems[index] = dataItems[(index * 2) + 1];
					dataItems[(index * 2) + 1] = temp;
					index = (index * 2) + 1;
				}
				else{
					return oldMax;
				}
			}
			else{
				return oldMax;
			}
		}
		return oldMax;
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: clear ()

// Removes all the data items from a heap.

{
	size = 0;  
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>:: isEmpty () const

// Returns true if a heap is empty. Otherwise, returns false.

{
	if (size == 0) { // some condition to prove that there is something in dataItems
		return true;
	}
	else {
		return false; // other wise the  dataItems heap is empty
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>:: isFull () const

// Returns true if a heap is full. Otherwise, returns false.

{
	if (size == maxSize) { // some condition to check if the heap is at the maxSize 
		return true;
	}
	else {
		return false; // otherwise the heap is not full 
	}
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}

//--------------------------------------------------------------------
//
//                        In-lab operations
//
//--------------------------------------------------------------------

//--------------------------------------------------------------------
//  In-lab Exercise 3
//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: writeLevels () const

// Outputs the data items in a heap in level order, one level per line.
// Only outputs the priority for each data item.

{
	// ignored as per instructions 
}

#endif	// #ifndef HEAP_CPP

