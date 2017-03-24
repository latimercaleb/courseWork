// Problem 1-2 programmed by Caleb Latimer
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	double x,y;
	double result; 
	cout << "The pattern is : " << 1 << -sqrt(2) << 2 << endl; 
	cout << "Enter the starting index : ";
	cin >> x;
	for (x; x < 100; x++)
	{
		y = pow((1)*(-sqrt(2)), x);
		cout << y << ", ";
	}
	result = pow((1)*(-sqrt(2)), 100);
	cout << "\n The sum is going to be : " << result << endl; 
		

}