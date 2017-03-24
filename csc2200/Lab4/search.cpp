//--------------------------------------------------------------------
//
//  Laboratory 4, Prelab                                search.cpp
//
//  Implementation of a binary search routine
//
//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool OrderedList<DataType,KeyType>:: binarySearch ( KeyType searchKey, int &index )

// Binary search routine. Searches a list for the data item with
// key searchKey. If the data item is found, then returns true with
// index returning the array index of the entry containing searchKey.
// Otherwise, returns false with index returning the array index of the
// entry containing the largest key that is smaller than searchKey
// (or -1 if there is no such key).

{
    int low  = 0,           // Low index of current search range
        high = size - 1;    // High index of current search range
    bool result;            // Result returned

    while ( low <= high )
    {
        index = ( low + high ) / 2;               // Compute midpoint
        if ( searchKey < dataItems[index].getKey() )
           high = index - 1;                      // Search lower half
        else if ( searchKey > dataItems[index].getKey() )
           low = index + 1;                       // Search upper half
        else
           break;                                 // searchKey found
    }

    if ( low <= high )
       result = true;       // searchKey found
    else
    {
       index = high;        // searchKey not found, adjust index
       result = false;
    }

    return result;
}

