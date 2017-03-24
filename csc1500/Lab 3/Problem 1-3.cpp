// Problem 1-3 of Lab 3 by Caleb Latimer
#include<iostream>
using namespace std;
int main()
{
	int result,x;
	cout << "Enter a number for x : ";
	cin >> x; 
	for (int i = x; i < 100; i++){
		result = ((i*pow(i + 1, 2)) / 4) / 3;
		cout << result << " ";
	}
	cout << "The result will be : " << result << endl; 
}