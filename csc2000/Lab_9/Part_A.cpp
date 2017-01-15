// Part A of Lab 9 programmed by Caleb Latimer

#include<iostream>
using namespace std;

int main()

{
	double grade;
	

	do {
		cout << "Tell me a grade." << endl;
		cin >> grade;
		

	} while (grade < 0 || grade > 100);

	cout << "The grade is :" << grade << endl;
	return 0;
}