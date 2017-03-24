// Lab 6 Problem 2 by Caleb Latimer

#include <iostream>
using namespace std;

int main()
{
	double temp,newTemp;
	char degree; 
	cout << "Hello user, give me a temp and include the degree type. " << endl;
	cin >> temp >> degree;
	
	switch (degree)
	{
	case 'F':
		newTemp = (5.0 / 9.0) * (temp - 32.0);
		cout << "The temp is : " << newTemp << "C" << endl;
		break;

	case 'f':
		newTemp = (5.0 / 9.0) * (temp - 32.0);
		cout << "The temp is : " << newTemp << "C" << endl;
		break;

	case 'C':
		newTemp = (9.0 / 5.0) * (temp)+32.0;
		cout << "The temp is : " << newTemp << "F" << endl; 
		break;

	case 'c':
		newTemp = (9.0 / 5.0) * (temp)+32.0;
		cout << "The temp is : " << newTemp << "F" << endl;
		break;

	default: 
		cout << "Statement invalid teerminating program \n "; 
	}
}