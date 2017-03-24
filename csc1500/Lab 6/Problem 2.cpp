// Problem 2 programmed by Caleb Latimer 
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
	double input;
	cout << "Enter Octal Fraction : ";
	cin >> input; 

	int base;
	double frac;
	base = input; 
	frac = input - base;

	int wholeDigit;
	cout << "Input the number of digits of the whole number : ";
	cin >> wholeDigit;
	int *result;
	result = new int[wholeDigit];
	int g = 0;

	do{
		int temp = 0;
		temp = base % 10;
		result[g] = temp * (pow(8, g));
		g++;
		base = base / 10;
	} while (base != 0);

	g--;

	int sum = 0;

	for (int i = g; i >= 0; i--)
		sum += result[i];

	int decimalDigit;
	cout << "Enter the number of digits after the decimals place : ";
	cin >> decimalDigit;

	double *fracRemainder;
	fracRemainder = new double[decimalDigit];
	int q = 0;
	int exp = -1;
	do{
		double copy = 0;
		int dumb = 0;
		int tem = 0;
		tem = frac * 10;
		fracRemainder[q] = tem * (pow(8, (exp)));
		exp--;
		q++;
		dumb = frac * 10;
		frac = frac * 10;
		frac = (frac - dumb) + 0.001;
	} while (q<decimalDigit);

	double newSum = 0;

	for (int i = 0; i < q; i++)
		newSum += fracRemainder[i];

	cout << endl;
	double t = sum + newSum;
	cout << "The Oct to Decimal conversion is : ";
	cout << setprecision(4) << showpoint << fixed << t << endl;
	return 0; 
}