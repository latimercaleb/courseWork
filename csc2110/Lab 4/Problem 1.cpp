// Problem 1 by Caleb Latimer 
// Declare array in main function and look up refference passing 
#include<iostream>
using namespace std;
void getinput(int myArray[], int size, int &V);
void checkArray(int myArray[], int size, int &flag); // Function prototypes, V is Flag 

int main()
{
	int V;
	int myArray[10];
	getinput(myArray, 10, V);
	checkArray(myArray, 10, V);
	//system("Pause");
}
void getinput(int myArray[], int size, int &V)
{
	cout << "Populate the array with 10 numbers: " << endl;
	for (int i = 0; i < size; i++) // Initialization loop
	{
		cin >> myArray[i];
	}
	cout << "Enter a number for V :" << endl; // Initialization request 
	cin >> V;
	
}
void checkArray(int myArray[], int size, int &flag)
{
	for (int i = 0; i < size; i++)
	{
		if (myArray[i] == flag)// Checks the flag for each element and only executes if found 
		{
			for (int k = i; k <(size- 1); k++)
			{
				myArray[k] = myArray[k + 1]; // myArray is now equal to the value to the right so everything shifts left.  
				myArray[k + 1] = 0;
				//cout << "Test2" << endl; 
			}

		} //cout << "Test" << endl; 
	}

	cout << "Your new array is " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << myArray[i] << " ";
	}
	cout << endl;

	//cout << flag << endl; 

}