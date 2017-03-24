
#include "QueueLinked.h"
template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr): dataItem(nodeData), next(nextPtr)
{ // Initializer list used above
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber = Queue<DataType>::MAX_QUEUE_SIZE): front(NULL), back(NULL)
{// Initializer list used above
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{
	if (this != &other) {
		*this = other; 
	}
}

template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{
	front = other.front; 
	while (other.front != other.back) {
		back.dataItem = other.front.dataItem;
		back = back->next;
		other.front = other.front->next;

	}
}

template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
	clear();
}

template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	if (isEmpty()) {
		front = new QueueNode(newDataItem, NULL);
		back = front;
	}
	else {
		back->next = new QueueNode(newDataItem,NULL);
		back = back->next;
	}
}

template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{ 
	if (isEmpty()) {
		throw logic_error("Cannot dequeue empty queue!!");
	}
	else {
		QueueNode *temp = front;
		front = front->next;
		return (temp->dataItem);
	}
}

template <typename DataType>
void QueueLinked<DataType>::clear()
{
	QueueNode *temp;
	while (front != back){
		temp = front;
		front = front->next;
		delete temp;
	}
	delete front; 
	front = NULL;
	back = NULL;
}

template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	if (front == NULL || back == NULL) {
		return true;
	}
	else {
		return false; 
	}
}

template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	return false; // always false linked list is never full 
}

template <typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{ 
	if (isEmpty()) {
		front = new QueueNode(newDataItem, NULL);
		back = front;
	}
	else {
		QueueNode *temp = new QueueNode(front->dataItem,front->next);
		front->dataItem = newDataItem;
		front->next = temp;
	}

}

template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	if (isEmpty()) {
		throw logic_error("Cannot getRear() of empty queue!!");
	}
	else {
		if (front == back) { // handles when they are only one 
			QueueNode*temp = back;
			dequeue();
			return temp->dataItem;
		}
		else {
			QueueNode *temp = new QueueNode (back->dataItem, NULL);
			QueueNode*prev = new QueueNode(front->dataItem, front->next);
			while (prev->next != back) {
				prev = prev->next;
			}
			back = prev;
			back->next->dataItem = NULL;
			return temp->dataItem;
		}
	}
}

template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
	int count = 1;
	QueueNode*nodeCounter = front;
	while (nodeCounter != back) {
		nodeCounter = nodeCounter->next;
		count++;
	}
	return count; 
}

template <typename DataType>
void QueueLinked<DataType>::showStructure() const
{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != '\0' ; p = p->next )
	{
	    if( p == front ) 
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}