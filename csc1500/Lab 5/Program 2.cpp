// Program 2 of lab 5 built by Caleb Latimer
#include<iostream>
#include<fstream>
#include<string>
// requires output.txt 
// the output should take duplicates into account and put them in increasing order
using namespace std;
int main(){
	// initialize the array from A1.txt
	int g = 0; // counter needed 
	ifstream doc;
	doc.open("A1.txt");
	int * myArray;
	myArray = new int[1000]; // from problem 1 
	/*int *resultsArray; // second array might be needed to hold and output  swaps 
	resultsArray = new int[1000];*/

	while (!doc.eof()){// Initialize array from text file
		doc >> myArray[g];
		g++;
	}
	/*for (int i = 0; i < g; i++){  // check to ensure array read in properly 
		cout << myArray[i] << " ";
	}*/
	// Insertion sort here....
	int key = myArray[0];
	int temp;
	for (int j = 1; j < g; j++)
	{ 
		int i = 0;
		while (myArray[j] >myArray[i])
			i += 1;
		key = myArray[j];
		for (int k = 0; k < (j - i - 1); k++)// referrence pseudocode in slides for the next step of how to solve for this 
		{// ^^^ what am I am missing????
			myArray[j-k] = myArray[j-k-1]; // Needs to modify index
			myArray[i] = key;

			//myArray[j+1] = myArray[j];
			//myArray[j] = temp; // swap
		}
	}
	// Output to A2Output.txt
	ofstream results; // creates output file
	results.open("A2Output.txt"); 
	/*int x = 2;
	pow(x, 2);*/

	for (int i = 0; i < g; i++)
		results << myArray[i] << " "; // prints to output file the sorted array 
	doc.close(); /// Closes doc now that it's job is done.
	system("pause");
}
