// Problem 4 of Lab 4 programmed by Caleb Latimer
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream myDoc, myDoc2;
	myDoc.open("A4.txt");
	myDoc2.open("B4.txt");
	int myFirstArray[4][4];
	int mySecondArray[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			myDoc >> myFirstArray[i][j];
			myDoc2 >> mySecondArray[i][j];

		}
	}
	// Test for visibillity
	cout << "My first array is :\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << myFirstArray[i][j] << " ";

		}
		cout << endl;
	}
	cout << "My second array is :\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << mySecondArray[i][j] << " ";

		}
		cout << endl; 
	}
	int myResult[4][4]; // solution array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			myResult[i][j] = 0; // Initializing to 0 

		}
	}
	cout << "My sum is : \n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			myResult[i][j] = myFirstArray[i][j] + mySecondArray[i][j]; // math to populate each element of matrix
			cout << myResult[i][j] << " "; // output result 

		}
		cout << endl; // line to form matrix shape 
	}

}