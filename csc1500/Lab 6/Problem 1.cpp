// Problem 1 programmed by Caleb Latimer
// Converting from decimal to binary 
#include<iostream>
using namespace std;
int main(){
	int *r, size;
	int input; 
	int quotient = 100; 

	cout << "Input a whole number : ";
	cin >> input;  

	cout << "Base digits are " << input << endl;

	r = new int[1000]; // try a better way of coming up with an index 
	int temp; 
	int i = 0;
	size = 0;
	while (quotient > 0){
		quotient = input / 2; 
		r[i] = input % 2;
		i++; 
		size++;
		input = quotient;
	}

	for (int i = size-1; i >= 0; i--)
		cout << r[i] << " ";
	cout << endl; 
	return 0; 
}