// Lab 3 Question 1 programmed by Caleb Latimer

#include <iostream> 
#include <iomanip> // Calling libraries
using namespace std;

int main()
{
	double kg, pound; // Declaring vars 

	cout << " What is the weight in kg?" << endl; // User prompt
	cin >> kg;
	pound = kg*2.2; // Computation
	cout << fixed << showpoint << setprecision(2); // Sets computation to 2 digits after decimal 
	cout << "That weight converted to pounds is " << pound << endl; // Outputs solution 
	return 0;
}