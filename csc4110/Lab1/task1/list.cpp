// Implementation for list.h
#include "list.h"
#include <iostream>
using namespace std;
//list::node::node() {
//	data = 0;
//	next = nullptr;
//}
//list::node::node(double number) {
//	data = number;
//	next = nullptr;
//}
list::list(){
	// Default Constructor, initializes head to 0 and points to null, increase count
	head = new node(0);
	count = 1;
}
list::list(double input, node* next) {
	// Parameter Constructor, initializes head's members with parameters, increase count
	head = new node(input);
	head->next = next;
	count = 1;
}

list::~list() {
	// Traverse list and remove each node to prevent memory leaks
	ptr = head;
	while (ptr != NULL) {
		ptr = head->next;
		delete head;
		head = ptr;
	}
}

void list::insert(double input) {
	// Check if cap of 100 is reached, if not insert node as the new head while retaining the previous nodes
	if (count == 100) {
		cout << "100 node limitation reached cannot insert " << endl;
	}
	else {
		ptr = new node(input);
		ptr->next = head;
		head = ptr;
		count++;
	}
}

int list::isEmpty() {
	// Determines if list is empty based off of count, count is never 0 because of the constructor's implementation however
	if (count == 0) {
		return 1; // for empty
	}
	else {
		return 0; // for not empty
	}
}

int list::numOfElements() {
	// Returns the number of nodes that currently are in the list
	return count;
}

void list::printList() {
	// Additional function to view the ordering of the list 
	ptr = head;
	cout << "The current list is: " << ptr->data << " , ";
	while (ptr->next != nullptr) {
		ptr = ptr->next;
		cout << ptr->data << " , ";
	}
}