// Lab 18 written by Caleb Latimer
#include<iostream>
#include<cmath>
using namespace std;
int square(int); // must be recursive
int main(){
	int input,result;
	cout << "Enter your input value (it must be nonnegative): ";
	cin >> input;
	result = square(input);
	return 0;
}
int square(int in)
{
	int static sum = 0;
	if (in == 0){
		cout << sum <<endl;
		return 0;
	}
	else
	{
		sum += (pow(in, 2));
		return square(in-1);
	}
}