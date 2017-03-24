// Problem 1-4 programmed by Caleb Latimer
#include <iostream>
using namespace std;
int main()
{
	double x,n,j, sum =0; 
	cout << "Enter a number n : ";
	cin >> n; 
	cout << "And a number j : ";
	cin >> j;
	for (int i = n; i < j; i++){
		x = pow(i, 2);
		cout << x << " ";
		sum += x;
	}
	cout << "\n The sum is : " << sum << endl; 
}