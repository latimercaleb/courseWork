// Problem 3 of Lab 4 programmed by Caleb Latimer
#include<iostream>
#include <fstream>
using namespace std;
int main()
{ 
	ifstream myDoc;
	myDoc.open("B3.txt");
	int myArray[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			myDoc >> myArray[i][j];
			cout << myArray[i][j]; // test for visibility
		}
		cout << endl; // test for visibility
	}
	cout << "\nThe tranposed matrix is :\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//myArray[i][j] = myArray[j][i]; this line is not needed because transposing is the flipping of row and column
			cout << myArray[j][i];
		}
		cout << endl;
	}

}