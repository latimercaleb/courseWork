
#include "QueueArray.h"

template <typename DataType>
QueueArray<DataType>::QueueArray(int maxNumber)
{
	maxSize = maxNumber;
	front = -1;
	back = front;
	dataItems = new DataType[maxSize];
}

template <typename DataType>
QueueArray<DataType>::QueueArray(const QueueArray& other)
{
	if (this != &other) {
		this = other;
	}
}

template <typename DataType>
QueueArray<DataType>& QueueArray<DataType>::operator=(const QueueArray& other)
{
	maxSize = other.maxSize;
	dataItems = new DataType[maxSize];
	if (!other.isEmpty()) {
		for (int count = 0; count < other.back; count++) {
			dataItems[count] = other.dataItems[count];
		}
		front = other.front;
		back = other.back;
	}
	else {
		front = -1;
		back = front;
	}
}

template <typename DataType>
QueueArray<DataType>::~QueueArray()
{
	clear();
}


template <typename DataType>
void QueueArray<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty()) {
		front = 0;
		back = 0;
		dataItems[front] = newDataItem;
	}
	else if (isFull()) {
		throw logic_error("Queue is full cannot enqueue!!");
	}
	else {
		back = (back+1)%maxSize;
		dataItems[back] = newDataItem;
	}
}

template <typename DataType>
DataType QueueArray<DataType>::dequeue() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("Cannot dequeue empty queue!!");
	}
	else {
		DataType temp = dataItems[front];
		dataItems[front] = NULL;
		if (!isEmpty()) {
			front = (front + 1) %maxSize;
		}
		else {
			front = 0;
		}
		return temp;
	}
}

template <typename DataType>
void QueueArray<DataType>::clear()
{
	front = -1;
	back = -1;
	delete[]dataItems;
}

template <typename DataType>
bool QueueArray<DataType>::isEmpty() const
{
	if (front < 0 || back < 0) {
		return true;
	}
	else {
		return false;
	}
}

template <typename DataType>
bool QueueArray<DataType>::isFull() const
{
	if (getLength()== maxSize) {
		return true;
	}
	else {
		return false;
	}
}

template <typename DataType>
void QueueArray<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty()) {
		front = 0;
		back = 0;
		dataItems[front] = newDataItem;
	}
	else if (isFull()) {
		throw logic_error("Queue is full cannot enqueue!!");
	}
	else {
		front = (front + maxSize - 1) % maxSize;
		dataItems[front] = newDataItem;
	}
}

template <typename DataType>
DataType QueueArray<DataType>::getRear() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("Cannot dequeue empty queue!!");
	}
	else {
		DataType temp = dataItems[back];
		dataItems[back] = NULL;
		if (!isEmpty()) {
			back = (back - 1) % maxSize;
		}
		else {
			back = 0;
		}
		return temp;
	}
}

template <typename DataType>
int QueueArray<DataType>::getLength() const
{
	if (front < back)
		return back - front;
	else
		return (maxSize - ((front - back) - 1));
	/*return myDataItems.size();
	if (front < back)
		return (back - front) + 1;
	else
		return (abs(back - front) + 1);*/
	//return (back-front)+maxSize;
	//return (back-front)*maxSize;
}

//--------------------------------------------------------------------

template <typename DataType>
void QueueArray<DataType>::showStructure() const 
// Array implementation. Outputs the data items in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
    int j;   // Loop counter

    if ( front == -1 )
       cout << "Empty queue" << endl;
    else
    {
       cout << "Front = " << front << "  Back = " << back << endl;
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       if ( back >= front )
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) && ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       else
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) || ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       cout << endl;
    }
}