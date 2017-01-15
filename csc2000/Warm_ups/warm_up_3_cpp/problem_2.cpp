// Warm up 3 practice 2 programmed by Caleb Latimer
#include <iostream>
using namespace std;

int main()
{
	double test, test2, test3, test4, test5, testAvg; // Variable declaration 
	cout << "Enter 5 test scores " << endl; // User prompt
	cin >> test; // Variable assignment 
	cin >> test2;
	cin >> test3;
	cin >> test4;
	cin >> test5;

	testAvg = (test + test2 + test3 + test4 + test5) / 5; 

	cout << "The total test average is " << testAvg << endl;// Average display 
	return 0;
}