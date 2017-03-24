// Problem 1 programmed by Caleb Latimer
#include<iostream>
using namespace std;

int main()
{
	int grade[8],total,avg;
	total = 0; // Vars declared and total assigned to zero initially due to using a compound operator below
	
	for (int i = 0; i < 8; i++) // First for loop will take in inputs, each input it will add to total so that at the end total is the complete sum of the array
	{
		cin >> grade[i];
		total += grade[i];
	}

	cout << endl; // Gives me a blank space in order to better see my outputs 

	for (int j = 0; j < 8; j++) // This for loop takes the data read in earlier and reads it out marking it with * to fully clarify the difference
		cout << grade[j] << '*' << endl;
	
     avg = total / 8; // Calculates average
	 cout << "The total average is " << avg << endl; // Outputs avg to user 

}