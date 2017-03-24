//--------------------------------------------------------------------
//
//  Laboratory 11, Programming Exercise 2                 heapsort.cpp
//
//  
//
//--------------------------------------------------------------------

template < typename DataType >
void moveDown ( DataType dataItems [], int root, int size )

// Restores the binary tree that is rooted at root to a heap by moving
// dataItems[root] downward until the tree satisfies the heap property.
// Parameter size is the number of data items in the array.

{
    DataType insertDataItem;  // Data item to be inserted -- dataItems[root]
    int stop,           // (Re)insertion point found
        j;              // Array index that moves down the heap

    insertDataItem = dataItems[root];
    stop = 0;
    j = 2*root+1;
    while ( j < size  &&  !stop )
    {
        if ( j < size-1  &&
             dataItems[j].getPriority() < dataItems[j+1].getPriority() )
           j++;
        if ( insertDataItem.getPriority() >= dataItems[j].getPriority() )
           stop = 1;
        else
        {
           dataItems[(j-1)/2] = dataItems[j];
           j = 2*j+1;
        }
    }
    dataItems[(j-1)/2] = insertDataItem;
}

//--------------------------------------------------------------------

template < typename DataType >
void heapSort ( DataType dataItems [], int size )

// Heap sort routine. Sorts the data items in the array in ascending
// order based on priority.

{

}

