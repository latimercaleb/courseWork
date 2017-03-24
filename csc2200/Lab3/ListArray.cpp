

#include "ListArray.h"

template < typename DataType >
List<DataType>::List ( int maxNumber )
{
	maxSize = maxNumber;
	dataItems = new DataType[maxSize];
	size = 0;// the size increases with insertion
	cursor = 0; // sets cursor to the first value in list
	for (int i =0; i<maxSize; i++)
		dataItems[i] = NULL;
	
}

template < typename DataType >
List<DataType>::List ( const List& source )
{
	*this = source; // should be handled by copy constructor
}
    
template < typename DataType >
List<DataType>& List<DataType>::operator= ( const List& source )
{
	if (this != &source)
	{
		maxSize = source.maxSize;
		size = source.size;
		cursor = source.cursor;
		//delete []dataItems; // clears dataItems, weird run-time error here. Why? 
		dataItems = new DataType[maxSize];
		for (int count = 0; count < maxSize; count++)
			dataItems[count] = source.dataItems[count];
	}
		// else do nothing, they are the same so no copy is made
		return *this;
}

template < typename DataType >
List<DataType>::~List ()
{
	maxSize = 0;
	size = 0;
	cursor = -1;
	delete[] dataItems;
}

template < typename DataType >
void List<DataType>::insert ( const DataType& newDataItem )
	throw ( logic_error )
{
	if (isFull())
		throw;
	else
	{
		if (isEmpty())
			dataItems[cursor] = newDataItem;
		else
			dataItems[++cursor] = newDataItem;

		size++;
	}
}

template < typename DataType >
void List<DataType>::remove () throw ( logic_error )
{
	if (isEmpty())
		throw;
	else
		{
			dataItems[cursor] = NULL;
			if (cursor == (size-1))
				cursor = 0;
			else
				cursor++;
		
			size--;
		}
}

template < typename DataType >
void List<DataType>::replace ( const DataType& newDataItem )
	throw ( logic_error )
{
	if (isEmpty())
		throw;
	else
		dataItems[cursor] = newDataItem; 
}

template < typename DataType >
void List<DataType>::clear ()
{
	for (int count = 0; count < maxSize; count++)
		dataItems[count] = NULL;
	size = 0;
}

template < typename DataType >
bool List<DataType>::isEmpty () const
{
	if (size == 0)
		return true;
	else
		return false;
}

template < typename DataType >
bool List<DataType>::isFull () const
{
	if (size == maxSize)
		return true;
	else
		return false;
}

template < typename DataType >
void List<DataType>::gotoBeginning ()
        throw ( logic_error )
{
	if (isEmpty())
		throw;
	else
		cursor = 0;
}

template < typename DataType >
void List<DataType>::gotoEnd ()
        throw ( logic_error )
{
	if (isEmpty())
		throw;
	else
		cursor = maxSize-1;
}

template < typename DataType >
bool List<DataType>::gotoNext ()
        throw ( logic_error )
{
	if (isEmpty())
		throw;
	else
	{
		if (cursor!=maxSize-1) {
			cursor++;
			return true;
		}
	}
	return false;
}

template < typename DataType >
bool List<DataType>::gotoPrior ()
        throw ( logic_error )
{
	if (isEmpty())
		throw;
	else
	{
		if (cursor != 0) {
			cursor--;
			return true;
		}
	}
	return false;
}

template < typename DataType >
DataType List<DataType>::getCursor () const
        throw ( logic_error )
{
	return dataItems[cursor];
}

#include "show3.cpp"

template < typename DataType >
void List<DataType>::moveToNth ( int n )
        throw ( logic_error )
{
	cursor = n; 
}

template < typename DataType >
bool List<DataType>::find ( const DataType& searchDataItem )
        throw ( logic_error )
{
	for (int i = 0; i <= size; i++) {
		if (dataItems[i] == searchDataItem)
			return true;
	}
	return false;
}