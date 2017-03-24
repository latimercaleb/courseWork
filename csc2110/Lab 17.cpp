// Lab 17 programmed by Caleb Latimer 
#include<iostream>
#include<cmath> // inlcuded for use of the square root function
#include<string> // included for what()
using namespace std;
// User defined exception classes 
class sqrtOfNeg{
public:
	sqrtOfNeg()
	{
		mes = "You tried to solve the root of a number less than zero";
	}
	string what()
	{
		return mes;
	}
private:
	string mes;
}son; // exception of square roots of negative numbers
class failInput{
public:
	failInput()
	{
		mes = "You failed to input the right thing. Try again!";
	}
	string what()
	{
		return mes;
	}
private:
	string mes;
}fi;// exception of failed input
class divideByZero{
public:
	divideByZero()
	{
		mes = "Your divisor is set to zero";
	}
	string what()
	{
		return mes;
	}

private:
	string mes;
}dbz; // exception of divide by zero 
// User defined functions 
// Division function 
void divide()
{
	try
	{
		int divisor, dividend, quotient;
		cout << "You have chosen to divide 2 numbers " << endl;
		cout << "Please enter the two numbers : ";
		cin >> dividend >> divisor;
		if (!cin)
			throw fi;
		if (divisor == 0)
			throw dbz;
		quotient = dividend / divisor;
		cout << "The result is :" << quotient << endl;
	}
	catch (failInput h)
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << h.what() << endl;
		divide();
	}
	catch (divideByZero b)
	{
		cout << b.what() << endl;
		divide();
	}
}
// Square root function
void square()
{
	// include try-catch statements
	try{
		double a, result;
		cout << "You have chosen to find the square root of a number " << endl;
		cout << "Enter the number " << endl;
		cin >> a;
		if (!cin)
			throw fi;
		if (a < 0)
			throw son;
		result = sqrt(a);
		cout << "The result is " << result << endl;
	}
	catch (failInput h)
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << h.what() << endl;
		square();
	}
	catch (sqrtOfNeg b)
	{
		cout << b.what() << endl;
		square();
	}
}
// Addition function (3rd choice)
void add()
{
	try{
		int a, b, sum;
		cout << "You have chosen to add 2 numbers " << endl;
		cout << "Input the two numbers : ";
		cin >> a >> b;
		if (!cin)
			throw fi;
		sum = a + b;
		cout << "The result is : " << sum << endl;
	}
	catch (failInput h)
	{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << h.what() << endl;
		divide();
	}
}
// Main menu designed to run infinitely unless user exits from main menu calls other functions here. 
void MainMenu()
{
	int r = 0;
	while (true)
	{
		cout << "Welcome to the calculator v2.1!" << endl; 
		cout << "Enter a choice for the following options" << endl;
		cout << "Enter 1 for division" << endl;
		cout << "Enter 2 for square root" << endl;
		cout << "Enter 3 for addition" << endl;
		cout << "Enter 4 to exit" << endl;
		cin >> r;
		if (r == 1)
		divide();
		else if (r == 2)
		square();
		else if (r == 3)
		add();
		else
		break;
	}
}
int main()
{
	MainMenu();// main calls menu
	return 0;
}