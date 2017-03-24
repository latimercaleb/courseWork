// Problem 3 programmed by Caleb Latimer 
#include<iostream>
using namespace std;

int main(){
	int input;
	cout << "Enter an integer greater than or equal to 2 : ";
	cin >> input;
	while (input < 2){
		cout << "Invalid input, try again.\n";
		cin >> input;
	}

	int test = 2;
	cout << input << "= ";
	while (test*test <= input){
		if (input % test == 0){
			cout << "*" << test;
			input = input / test;
		}
		else
			test++;
	}
	if (input > 1)
		cout << "*" << input;
	cout << endl;
	return 0; 
}