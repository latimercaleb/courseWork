#pragma once
// Header file for list 
class list {

public:
	class node {
	public:
		double data; // value of node
		node *next; // link to next node
		node()
		{ // Constructor for node sets to 0 and nullptr
			data = 0;
			next = nullptr;
		}
		node(double input)
		{ // Parameter constructor for node allowing input of data directly
			data = input;
			next = nullptr;
		}

	};

	node * ptr; // Additional public pointer for functional support
	list(); // List constructor
	list(double,node*); // List parameter constructor
	~list(); // List destructor

	// Methods
	void insert(double); // Inserts an element with the value number at the beginning of the list as the head
	int isEmpty(); // Returns 1 if the list is empty 0 otherwise, never returns 1 because list is initialized with a node
	int numOfElements(); // Returns the number of elements in the list 
	void printList(); // Prints the numbers in the list

private:
	node *head; // Initial node in the list
	int count; // Counter, iterates everytime a new number is added, utilized in insert() and numOfElements()
};