//--------------------------------------------------------------------
//  Laboratory 5                                        ListLinked.cpp
//
//  
//--------------------------------------------------------------------

#ifndef LISTLINKED_CPP
#define LISTLINKED_CPP

using namespace std;

#include <iostream>			// For showStructure
#include "ListLinked.h"

template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData,
	ListNode* nextPtr)
	// Creates a list node containing item elem and next pointer
	// nextPtr.
{
	this->dataItem = nodeData;
	this->next = nextPtr;
}

//--------------------------------------------------------------------

template <typename DataType>
List<DataType>::List(int ignored) :head(NULL), cursor(NULL)

// Creates an empty list. The argument is included for compatibility
// with the array implementation (maxSize specifier) and is ignored.

{
	//ListNode(ignored,NULL);
	//// content is unneeded since the list is empty 
	//// breaks here for some reason 
	//head = NULL;
	//next = NULL;
}

//--------------------------------------------------------------------

template <typename DataType>
List<DataType>::List(const List& other)

// Copy constructor. Creates a list which is equivalent in content
// to the "other" list.

{
	if (this != &other) {
		*this = other;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
// Overloaded assignment operator. Reinitializes the list to be 
// equivalent in content to the "other" list.
{
	this->head = other->head;
	ListNode temp = other->head;
	//temp->head = other->head; 
	while (temp->next != NULL) {
		// code to add new node here
		this->insert(temp->dataItem);
		temp = temp->next;
	}
	this->cursor = this->head;
}
//--------------------------------------------------------------------
template <typename DataType>
List<DataType>::~List()

// Destructor. Frees the memory used by a list.

{
	ListNode* current = head;
	ListNode* next = current->next;
	while (current != NULL) {
		delete current;
		current = next;
		next = current->next;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) item in the list.
// In either case, moves the cursor to newDataItem.

{
	if (isEmpty()) {
		head = new ListNode(newDataItem, NULL);
		cursor = head;
	}
	else {
		ListNode * current;
		current = cursor;
		cursor = new ListNode(newDataItem, current->next);
		current->next = cursor;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::remove() throw (logic_error)

// Removes the item marked by the cursor from a list. Moves the
// cursor to the next item in the list. Assumes that the first list
// item "follows" the last list item.

{
	ListNode *temp = cursor;
	ListNode *previousNode = head;
	if (temp->next == NULL){
		while (previousNode->next != cursor) {
			previousNode = previousNode->next;
		}
		cursor = previousNode;
		delete temp;

	}
	else if (temp != head){
		while (previousNode->next != cursor) {
			previousNode = previousNode->next;
			//previousNode++;
		}
		cursor = temp->next;
		previousNode->next = cursor;
		delete temp;
	}
	else{
		delete head;
	}
	
}

//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)

// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.

{
	ListNode* temp;
	temp = cursor;
	temp->dataItem = newDataItem;
}

//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::clear()

// Removes all the items from a list. Sets head and cursor to 0.

{
	head->dataItem = 0;
	head->next = NULL;
	cursor = head;
}

//--------------------------------------------------------------------

template <typename DataType>
bool List<DataType>::isEmpty() const

// Returns true if a list is empty. Otherwise, returns false.

{
	if (head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
bool List<DataType>::isFull() const

// Returns true if a list is full. Otherwise, returns false.

{
	return false; // always because a linked-list is never full 
}

//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
// If a list is not empty, then moves the cursor to the beginning of
// the list. If list is empty, throws logic error.
{
	if (!isEmpty()) {
		cursor = head;
	}
	else {
		throw logic_error("List is empty");
	}
}

//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)

// If a list is not empty, then moves the cursor to the end of the
// list. Otherwise, throws logic_error.

{
	if (!isEmpty()) {
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
	}
	else {
		throw logic_error("List is empty");
	}
}

//--------------------------------------------------------------------

template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise, 
// leaves cursor unmoved and returns false.

{
	if (cursor != NULL) {
		cursor = cursor->next;
		return true;
	}
	else {
		throw logic_error("List is empty");
		return false;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	if (cursor != head) {
		// how to do this? 
		ListNode *temp;
		temp = head;
		while (temp->next != cursor) {
			temp = temp->next;
		}
		cursor = temp;

	}
	else {
		throw logic_error("List is empty");
		return false;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)

// Returns the item marked by the cursor. Requires that list is not empty.

{
	if (!isEmpty()) {
		return cursor->dataItem;
	}
	else {
		throw logic_error("List is empty");
		return 0;
	}
}

//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
	if (isEmpty())
	{
		cout << "Empty list" << endl;
	}
	else
	{
		for (ListNode* temp = head; temp != 0; temp = temp->next) {
			if (temp == cursor) {
				cout << "[";
			}

			// Assumes that dataItem can be printed via << because
			// is is either primitive or operator<< is overloaded.
			cout << temp->dataItem;

			if (temp == cursor) {
				cout << "]";
			}
			cout << " ";
		}
		cout << endl;
	}
}

//--------------------------------------------------------------------
//
//                        Programming Exercises 2 and 3
//
//--------------------------------------------------------------------

// Programming exercise 2

template < typename DataType >
void List<DataType>::moveToBeginning() throw (logic_error)

// Removes the item marked by the cursor from a list and
// reinserts it at the beginning of the list. Moves the cursor to the
// beginning of the list.

{
	ListNode* temp;
	temp = head;
	head = cursor;
	head->next = temp;
	cursor = head;
}

//--------------------------------------------------------------------
// Programming exercise 3

template < typename DataType >
void List<DataType>::insertBefore(const DataType &newDataItem)
throw (logic_error)

// Inserts newDataItem before the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) item in the list.
// In either case, moves the cursor to newDataItem.

{
	if (isEmpty()) {
		head = new ListNode(newDataItem, NULL);
		cursor = head;
	}
	else {
		ListNode* previousNode;
		previousNode = head;
		while (previousNode->next != cursor) {
			previousNode = previousNode->next;
		}
		previousNode->next = new ListNode(newDataItem, cursor);
		cursor = previousNode->next;
	}
}

#endif		// #ifndef LISTLINKED_CPP



















////--------------------------------------------------------------------
////  Laboratory 5                                        ListLinked.cpp
////
////  
////--------------------------------------------------------------------
//
//#ifndef LISTLINKED_CPP
//#define LISTLINKED_CPP
//
//using namespace std;
//
//#include <iostream>			// For showStructure
//
//#include "ListLinked.h"
//
//template <typename DataType>
//List<DataType>::ListNode::ListNode(const DataType& nodeData,
//				   ListNode* nextPtr)
//// Creates a list node containing item elem and next pointer
//// nextPtr.
//{
//	this->dataItem = nodeData;
//	this->next = nextPtr;
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//List<DataType>::List(int ignored)
//
//// Creates an empty list. The argument is included for compatibility
//// with the array implementation (maxSize specifier) and is ignored.
//    
//{
//	//ListNode(ignored,NULL);
//	//// content is unneeded since the list is empty 
//	//// breaks here for some reason 
//	//head -> ignored;
//	//next -> NULL;
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//List<DataType>::List(const List& other)
//    
//// Copy constructor. Creates a list which is equivalent in content
//// to the "other" list.
//
//{
//	if (this != &other){
//		*this = other;
//	}
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//List<DataType>& List<DataType>::operator=(const List& other)
//// Overloaded assignment operator. Reinitializes the list to be 
//// equivalent in content to the "other" list.
//{
//	ListNode temp;
//	temp->head = other->head; 
//	while (temp->next != NULL){
//		// code to add new node here
//		temp->next = this->next;
//		temp = temp->next;
//	}
//}
////--------------------------------------------------------------------
//template <typename DataType>
//List<DataType>::~List() 
//
//// Destructor. Frees the memory used by a list.
//
//{
//	ListNode* current = head;
//	while (current != NULL) {
//		ListNode* next = current->next;
//		delete current;
//		current = next;
//	}
//	head ->dataItem = 0;
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
//
//// Inserts newDataItem after the cursor. If the list is empty, then
//// newDataItem is inserted as the first (and only) item in the list.
//// In either case, moves the cursor to newDataItem.
//
//{
//	if (isEmpty()) {
//		head = new ListNode(newDataItem, NULL);
//	}
//	else {
//		ListNode * current;
//		current = cursor;
//		cursor = new ListNode(newDataItem, current->next);
//		current->next = cursor;
//	}
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//void List<DataType>::remove() throw (logic_error) 
//
//// Removes the item marked by the cursor from a list. Moves the
//// cursor to the next item in the list. Assumes that the first list
//// item "follows" the last list item.
//
//{
//	ListNode *current = cursor;
//	ListNode *previousNode = head;
//	while (previousNode->dataItem != NULL && previousNode->next != cursor) {
//		//previousNode->previousNode.next;
//		previousNode++;
//	}
//	cursor = cursor->next;
//	previousNode->next = cursor;
//	delete current;
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
//
//// Replaces the item marked by the cursor with newDataItem and
//// leaves the cursor at newDataItem.
//
//{
//	ListNode* temp;
//	temp = cursor;
//	temp->dataItem = newDataItem;
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//void List<DataType>::clear() 
//
//// Removes all the items from a list. Sets head and cursor to 0.
//
//{
//	head->dataItem = 0;
//	head->next = NULL;
//	cursor = head;
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//bool List<DataType>::isEmpty() const 
//
//// Returns true if a list is empty. Otherwise, returns false.
//
//{
//	if (head == NULL) {
//		return true;
//	}
//	else {
//		return false; 
//	}
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//bool List<DataType>::isFull() const 
//
//// Returns true if a list is full. Otherwise, returns false.
//
//{
//    return false; // always because a linked-list is never full 
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//void List<DataType>::gotoBeginning() throw (logic_error)
//// If a list is not empty, then moves the cursor to the beginning of
//// the list. If list is empty, throws logic error.
//{
//	if (!isEmpty()) {
//		cursor = head;
//	}
//	else {
//		throw logic_error("List is empty");
//	}
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//void List<DataType>::gotoEnd() throw (logic_error)
//
//// If a list is not empty, then moves the cursor to the end of the
//// list. Otherwise, throws logic_error.
//
//{
//	if (!isEmpty()) {
//		while (cursor->next != NULL) {
//			cursor = cursor->next;
//		}
//	}
//	else {
//		throw logic_error("List is empty");
//	}
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//bool List<DataType>::gotoNext() throw (logic_error)
//
//// If the cursor is not at the end of a list, then moves the
//// cursor to the next item in the list and returns true. Otherwise, 
//// leaves cursor unmoved and returns false.
//
//{
//	if (cursor!=NULL) {
//			cursor = cursor->next;
//			return true;
//	}
//	else {
//		throw logic_error("List is empty");
//		return false;
//	}
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//bool List<DataType>::gotoPrior() throw (logic_error)
//
//// If the cursor is not at the beginning of a list, then moves the
//// cursor to the preceeding item in the list and returns true.
//// Otherwise, returns false.
//
//{
//	if (cursor!=head) {
//		// how to do this? 
//		ListNode *temp;
//		temp = head;
//		while (temp->next != cursor) {
//			temp++;
//		}
//		cursor = temp;
//
//	}
//	else {
//		throw logic_error("List is empty");
//		return false;
//	}
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//DataType List<DataType>::getCursor() const throw (logic_error)
//
//// Returns the item marked by the cursor. Requires that list is not empty.
//
//{
//	if (!isEmpty()) {
//		return cursor->dataItem;
//	}
//	else {
//		throw logic_error("List is empty");
//		//return -1;
//	}
//}
//
////--------------------------------------------------------------------
//
//template <typename DataType>
//void List<DataType>::showStructure() const
//
//// Outputs the items in a list. If the list is empty, outputs
//// "Empty list". This operation is intended for testing and
//// debugging purposes only.
//
//{
//    if ( isEmpty() )
//    {
//       cout << "Empty list" << endl;
//    } 
//    else
//    {
//	for (ListNode* temp = head; temp != 0; temp = temp->next) {
//	    if (temp == cursor) {
//		cout << "[";
//	    }
//
//	    // Assumes that dataItem can be printed via << because
//	    // is is either primitive or operator<< is overloaded.
//	    cout << temp->dataItem;	
//
//	    if (temp == cursor) {
//		cout << "]";
//	    }
//	    cout << " ";
//	}
//	cout << endl;
//    }
//}
//
////--------------------------------------------------------------------
////
////                        Programming Exercises 2 and 3
////
////--------------------------------------------------------------------
//
//// Programming exercise 2
//
//template < typename DataType >
//void List<DataType>:: moveToBeginning() throw ( logic_error )
//
//// Removes the item marked by the cursor from a list and
//// reinserts it at the beginning of the list. Moves the cursor to the
//// beginning of the list.
//
//{
//	ListNode* temp;
//	temp = head;
//	head = cursor;
//	head->next = temp;
//	cursor = head;
//}
//
////--------------------------------------------------------------------
//// Programming exercise 3
//
//template < typename DataType >
//void List<DataType>:: insertBefore ( const DataType &newDataItem )
//    throw ( logic_error )
//
//// Inserts newDataItem before the cursor. If the list is empty, then
//// newDataItem is inserted as the first (and only) item in the list.
//// In either case, moves the cursor to newDataItem.
//
//{
//	if (isEmpty()) {
//		head = new ListNode(newDataItem,NULL);
//		cursor = head;
//	}
//	else {
//		ListNode* previousNode;
//		previousNode = head;
//		while (previousNode->next != cursor) {
//			previousNode = previousNode->next;
//		}
//		previousNode->next = new ListNode(newDataItem, cursor);
//		cursor = previousNode->next;
//	}
//}
//
//#endif		// #ifndef LISTLINKED_CPP
