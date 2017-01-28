// exercise 1 Programmed by: Caleb Latimer

#include <iostream>
#include <string>
using namespace std; // In the lines above I am calling my libraries using the preprocessor
int main()
{
	float x;
	int y;
	char ch1, ch2;
	string name;   // Here I declare my variables, string is a new one

	cout << "Enter a character "; // In the following pairs the system demands info from user and assigns it to each variable
	cin >> ch1;

	cout << "Enter a number ";
	cin >> y;

	cout << "Enter another character ";
	cin >> ch2;

	cout << "Enter a name ";
	cin >> name;

	cout << "Enter a floating point value ";
	cin >> x;

	cout << endl << "ch1 = " << ch1 << endl; // In this last block the output statement sends to the dos screen 
	cout << "y = " << y << endl;
	cout << "ch2 = " << ch2 << endl;
	cout << "Name is = " << name << endl;
	cout << "x = " << x << endl;

	return 0; 
}