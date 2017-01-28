// Lab 7 programmed by Caleb Latimer 

#include <iostream>
using namespace std;

int main()
{
	cout << "Enter the car's year and weight : " << endl;
	int year, weight;
	cin >> year >> weight;

	if (year <= 1990){
		if (weight < 2700)
			cout << "The weight class is 1 and the Registration fee is $26.50." << endl;
		if (weight >= 2700 && weight <= 3800)
			cout << "The weight class is 2 and the Registration fee is $35.50." << endl;
		if (weight > 3800)
			cout << "The weight class is 3 and the Registration fee is $56.50." << endl;
	}

	else if (year >= 1991 && year <= 1999)
	{
		if (weight < 2700)
			cout << "The weight class is 4 and the Registration fee is $35.00." << endl;
		if (weight >= 2700 && weight <= 3800)
			cout << "The weight class is 5 and the Registration fee is $45.50." << endl;
		if (weight > 3800)
			cout << "The weight class is 6 and the Registration fee is $62.50." << endl;
	}

	else {
		if (weight < 3500)
			cout << "The weight class is 7 and the Registration fee is $49.50." << endl;
		if (weight >= 3500)
			cout << "The weight class is 8 and the Registration fee is $62.50." << endl;
		
	}
	return 0;
}