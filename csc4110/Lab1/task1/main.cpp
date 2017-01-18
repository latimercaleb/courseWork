// Main file for task1 
// Written by Caleb Latimer 
// For CSC 4111

// Header files
#include "list.h" // Header file for the linkedlist.h that I created 
#include<iostream> // Standard I/O
#include<ctime> // For random input generation
#include<cstdlib> // Also for random input generation
using namespace std; // Standard I/O

// Function definitions
void printCount(list &mine) {
	// Function to implement numOfElements in main() and output result
	int count = mine.numOfElements();
	cout << endl;
	cout << "Count: " << count << endl;

}

void isEmptyEvaluation(list &mine) {
	// Function to evaluate the state of the list being empty or not based off of isEmpty() applied to main()
	if (mine.isEmpty() == 1) {
		cout << "There are no nodes, list is empty" << endl;
	}
	else {
		cout << "List is not empty" << endl;
	}
}
double randomDouble(){
	// Function for random input generation used after initial test values to generate different random doubles to add to the list
	double output;
	srand(time(NULL));
	output = (rand() % 100 + 1);
	return output;
}
// Main function
int main() {
	cout << " v 2.0 This program is test the implementation of a linked list class." << endl;
	double first, next, input;
	int loopForRandom;
	//char choice;

	first = 1.89321; // 1st var for testing
	next = 2.756435; // 2nd var for testing

	list myList(2500.34,nullptr); // constructor()
	myList.printList();
	printCount(myList); // numOfElements()
	isEmptyEvaluation(myList); //  isEmpty()

	myList.insert(first); 
	myList.printList();
	printCount(myList);
	isEmptyEvaluation(myList);

	myList.insert(next); 
	myList.printList();
	printCount(myList);
	isEmptyEvaluation(myList);

	cout << "Input a double: ";
	cin >> input;

	myList.insert(input);
	myList.printList();
	printCount(myList);
	isEmptyEvaluation(myList);

	loopForRandom = 4;
	while (loopForRandom < 102) {
		// Loop restricted to 102 to test 100 limit cap, returns 3 outputs of the cap being reached
		input = randomDouble();
		myList.insert(input);
		myList.printList();
		printCount(myList);
		isEmptyEvaluation(myList);
		loopForRandom++;
	}
	return 0;
} 