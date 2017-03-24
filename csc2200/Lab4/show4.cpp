//--------------------------------------------------------------------
//
//  Laboratory 4                                          show4.cpp
//
//  Array implementation of the showStructure operation for the
//  OrderedList ADT.
//
//--------------------------------------------------------------------

#include "OrderedList.h"

template < typename DataType, typename KeyType >
void OrderedList<DataType,KeyType>:: showStructure () const

// Outputs the keys of the data items in a list. If the list is
// empty, outputs "Empty list". This operation is intended for
// testing and debugging purposes only.

{
    if ( size == 0 )
       cout << "Empty list" << endl;
    else
    {
       cout << "size = " << size
            <<  "   cursor = " << cursor << endl;
       for ( int j = 0 ; j < maxSize ; ++j )
           cout << j << "\t";
       cout << endl;
       for ( int j = 0 ; j < size ; ++j ) {
	   if( j == cursor ) {
               cout << "[" << dataItems[j].getKey() << "]\t";
	   } else {
               cout << dataItems[j].getKey() << "\t";
	   }
       }
       cout << endl;
    }
}

