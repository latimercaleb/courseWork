//--------------------------------------------------------------------
//
//  Laboratory 4                                         ordlist.cpp
//
//  Array implementation of the Ordered List ADT
//
//--------------------------------------------------------------------

#ifndef ORDEREDLIST_CPP
#define ORDEREDLIST_CPP

using namespace std;

#include "OrderedList.h"

//--------------------------------------------------------------------
template < typename DataType, typename KeyType >
OrderedList<DataType,KeyType>:: OrderedList ( int maxNumber ) : maxSize(source.maxSize), size(source.size), cursor(source.cursor)
// Creates an empty list by calling the List ADT constructor.
{

}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void OrderedList<DataType,KeyType>:: insert ( const DataType &newDataItem ) throw ( logic_error )

// Inserts newDataItem in its appropriate location within an ordered
// list. If a data item with the same key as newData already
// exists in the list, then updates that data item's data with
// newData's data. Moves the cursor to newData.

{
    
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool OrderedList<DataType,KeyType>:: retrieve ( const KeyType& searchKey, DataType &searchDataItem )

// Searches a list for the data item with key searchKey. If the
// data item is found, then moves the cursor to the data item,
// copies the data item to searchDataItem, and returns true.
// Otherwise, returns false without moving the cursor and with
// searchDataItems undefined.

{
    return false;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void OrderedList<DataType,KeyType>:: replace ( const DataType &newDataItem )
    throw ( logic_error )

// Replaces the data item marked by the cursor with newData and
// moves the cursor to newData.

{
   
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void OrderedList<DataType,KeyType>:: showStructure () const

// Outputs the keys of the data items in a list. If the list is
// empty, outputs "Empty list". This operation is intended for
// testing and debugging purposes only.

{ // copied from show4
	if (size == 0)
		cout << "Empty list" << endl;
	else
	{
		cout << "size = " << size
			<< "   cursor = " << cursor << endl;
		for (int j = 0; j < maxSize; ++j)
			cout << j << "\t";
		cout << endl;
		for (int j = 0; j < size; ++j) {
			if (j == cursor) {
				cout << "[" << dataItems[j].getKey() << "]\t";
			}
			else {
				cout << dataItems[j].getKey() << "\t";
			}
		}
		cout << endl;
	}
}

//--------------------------------------------------------------------
//
//  Facilitator function
//

template < typename DataType, typename KeyType >
bool OrderedList<DataType,KeyType>:: binarySearch ( KeyType searchKey, int &index )

// Binary search routine. Searches a list for the data item with
// key searchKey. If the data item is found, then returns true with
// index returning the array index of the entry containing searchKey.
// Otherwise, returns false with index returning the array index of the
// entry containing the largest key that is smaller than searchKey
// (or -1 if there is no such key).

{
	// copied from search.cpp
	int low = 0,           // Low index of current search range
		high = size - 1;    // High index of current search range
	bool result;            // Result returned

	while (low <= high)
	{
		index = (low + high) / 2;               // Compute midpoint
		if (searchKey < dataItems[index].getKey())
			high = index - 1;                      // Search lower half
		else if (searchKey > dataItems[index].getKey())
			low = index + 1;                       // Search upper half
		else
			break;                                 // searchKey found
	}

	if (low <= high)
		result = true;       // searchKey found
	else
	{
		index = high;        // searchKey not found, adjust index
		result = false;
	}

	return result;
}


template < typename DataType, typename KeyType >
void OrderedList<DataType,KeyType>:: merge ( const OrderedList<DataType,KeyType>& fromL ) throw ( logic_error )

// Merges the data items in list fromL into a list. Assumes that
// none of the data items in fromL occur in L already. The merge
// is done in a single pass through both lists.

{
   
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool OrderedList<DataType,KeyType>:: isSubset ( const OrderedList<DataType,KeyType> &subList )

// Returns true if every key in list subList also occurs in a list --
// that is, if the keys in subList are a subset of the keys in the list.
// Otherwise, returns false.

{
   return false;
}

#endif // #IFNDEF ORDEREDLIST_CPP
