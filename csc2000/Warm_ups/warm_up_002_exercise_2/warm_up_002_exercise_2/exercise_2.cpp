// Exercise 2 Programmed by Caleb Latimer

# include <iostream>
using namespace std;

int main()
{
	int a = 20, b = 7;
	double x = 20, y = 7, z = 0; // in this problem i have to have z store all of my solutions, and cannot hardcode numerical literals
	
	z = a + b;
	cout << a << " + " << b << " = " << z << endl;

	z = a - b;
	cout << a << " - " << b << " = " << z << endl;

	z = b - a;
	cout << b << " - " << a << " = " << z << endl;

	z = a * b;
	cout << a << " * " << b << " = " << z << endl;

	z = a / b;
	cout << a << " / " << b << " = " << z << endl;

	z = x / y;
	cout << x << " / " << y << " = " << z << endl;

	z = a % b;
	cout << a << " % " << b << " = " << z << endl;

	z = b % a;
	cout << b << " % " << a << " = " << z << endl;

	return 0;
}