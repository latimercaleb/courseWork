// Lab 19 programmed by Caleb Latimer 
#include<iostream>
using namespace std;
double comp(int base, int power){ // factor in doubles
	if (power < 0) // takes into account negative exponents
		return (1 / comp(base, -power));
	else{ // otherwise checks other things
		if (power == 0)
			return 1; // because anything to the power of zero is zero
		else if (power == 1)
			return base; // and anything to the power of itself is itself
		else
		{
			return (base *comp(base, power - 1));// computes powers 
		}
	}
}
int main()
{
	int x, pow;
	cout << "Enter a number :";
	cin >> x; // takes first input
	cout << "Enter a power : ";
	cin >> pow; // takes second one
	cout << "The answer would be : " << comp(x, pow) << endl;// computes power and outputs it
	return 0;
}