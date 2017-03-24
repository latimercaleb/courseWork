// Exercise 1

#include <iostream>
#include <string>
using namespace std;

int main()
{
	float x;
	int y;
	char ch1, ch2;
	string name;
	cout << "Enter a character";
	cin >> ch1;
	cout << "Enter a number";
	cin >> y;
	cout << "Enter another character";
	cin >> ch2;
	cout << "Enter a name";
	cin >> name;
	cout << "Enter a floating point value";
	cin >> x;
	// Display the values read
	cout << endl << "ch1 = " << ch1 << endl;
	cout << "y = " << y << endl;
	cout << "ch2 = " << ch2 << endl;
	cout << "Name is" << name << endl;
	cout << "x = " << x << endl;
	return 0; 
}