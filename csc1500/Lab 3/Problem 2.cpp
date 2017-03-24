// Problem 2 of lab 3 programmed by Caleb Latimer
#include<iostream>
using namespace std;
int static x = 1;
int main()
{
	int n;
	cout << "Input number of rows" << endl;
	cin >> n;
	for (int i = 0; i <= n; i++)
	{
		//int myNum = i + 1;
		for (int j = 1; j <= i; j++){
			cout << x << " ";
			x++; 
		}
	
			cout << endl;
		//myNum++
	}
}