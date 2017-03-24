// Problem 2 programmed by Caleb Latimer
#include<iostream>
using namespace std;
int gcd(int a, int b)
{
	if (b == 0)
		return a; 
	else
		return gcd(b, a%b);// does euclidean's algorithm
}
int main()
{
	int num1, num2;
	cout << "Enter the first number: ";
	cin >> num1; // grabs input
	cout << "Enter the second number: ";
	cin >> num2; // grabs input
	cout << "The solution is: " << gcd(num1, num2) << endl;// outputs calculation which is a value returning function
	return 0;
}