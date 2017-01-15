// Problem 2 of Lab 13 programmed by Caleb Latimer
#include<iostream>
#include <iomanip>
using namespace std;

void posNeg(int x[], int SIZE) // Function of type void to hold data
{
	int pos[20], neg[20]; // positive and negative arrays and their size to match the number of inputs 
    for (int i = 0; i < SIZE; i++) // for loop for reading through the input array and filling pos and neg with the respective values 
	{
		if (x[i] >= 0)
			pos[i] = x[i];
		else
			pos[i] = '*';
		if (x[i] < 0)
			neg[i] = x[i];
		else
			neg[i] = 0;
    }
    cout << "The following are my positive array: pos"; // Opening statement for positive readout
	for (int j = 0; j < SIZE; j++) // Sets up for loop to scan array pos
	if (pos[j] != '*') // Sentinel set here to ensure that all '*' are removed from the index of pos
		cout << setw(5) << pos[j] << setw(5); // Returns pos with only pos & 0 values
	cout << endl;
	cout << endl; // double space for better readability 
	cout << "The following are my negative array: neg"; // opening for negative readout
	for (int k = 0; k < SIZE; k++) // sets up loop to scan array neg
	if (neg[k]!= 0) // sentinel in place to remove all 0 values from the index
		cout << setw(5)<< neg[k] << setw(5); // returns neg with only negative numbers in it's index 
}
int main()
{
	int alpha[20] = {1,2,58,98,-5,-232,0,1213,0,15,-56,12,3568,45,78,-89,23,84,1,32}; // initial function with initialized index 20 numbers 4 negative
	posNeg(alpha, 20); // summons function posNeg to do work and readout values 
}