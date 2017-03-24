// Problem 3 of lab 3 programmed by Caleb Latimer
#include<iostream>
using namespace std;
int fibcomp(int here)
{
	int sum = (here)+(here + 1);
	if (here == 0){
		return sum;
	}
	return fibcomp(here - 1);
}
int main()
{
	int num;
	int sum; 
	cout << "Enter a number between 1 and 100 : ";
	cin >> num;
	while (num <= 0 || num > 100){
		cout << "Invalid number passed\n";
		cin >> num;
	}
	sum = fibcomp(num);
	cout << "The sum is : " << sum << endl; 
}