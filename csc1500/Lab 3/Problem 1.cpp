// Problem 1 of lab 3 programmed by Caleb Latimer
#include<iostream>
using namespace std;
int main()
{
	int x; // this will be the xth term
	int static num =7; // static so as to only get bigger and bigger
	int sum = num;
	cout << "This is the first sequence of numbers : " << " -1, 1, 3, 5, 7 " << endl;
	cout << "Enter an end term ";
	cin >> x;
	cout << "The pattern is -1, 1, 3, 5, 7, ";
	for (int i = 0; i < x; i++)
	{
		num += 2;
		cout << num << ", ";
		sum += num;
	}
	cout << "\nThe total sum is : " << sum << endl; 
	return 0; 
}