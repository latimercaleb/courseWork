// Question 3 from Lab 1 programmed by Caleb Latimer
#include <iostream>
#include <cmath>
using namespace std; // Calling Libraries 

int main()
{
	double wire_length, cir_radius, cir_area; // Setting variables

	double const pi = 3.1416; // Setting constant to be pi 

	cout << "Wire length ? \n";
	cin >> wire_length; // Gets wire length from user


	cir_radius = (wire_length / (2 * pi));
	cir_area = pi * pow(cir_radius, 2);

	cout << "Circle frame radius is " << cir_radius << endl;
	cout << "Circle frame area is " << cir_area << endl;

	return 0; 
}