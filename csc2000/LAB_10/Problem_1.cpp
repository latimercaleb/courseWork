// Problem 1 of Lab 10 by Caleb Latimer

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double calculate_charge(double hours);

int main()
{  
	
	double x, total, total_charge;
	cout << showpoint << setprecision(2) << fixed << endl;
	cout << "Enter the hours for 3 cars with spaces in between : \n";
	total = 0;
	total_charge = 0;
	bool g = false;
	// for or do while for the number of cars 
	 
	
	for (int i = 1; i <= 3; i++)
	{
		cin >> x;
		if (g==false)
		{
			cout << "Car" << setw(10) << "Hours" << setw(10) << "Charge" << endl;
			g = true;
		}
		
		cout << i << setw(10)<< setprecision(1) << x << setw(10)<< setprecision(2) << calculate_charge(x) << endl; 
		total += x;
		total_charge += calculate_charge(x);
	}
	cout << "TOTAL" << setprecision(1) << setw(6) << total << setw(10) << setprecision(2) << total_charge << endl;
	return 0; 
}

double calculate_charge(double hours)
{
	
	double charge;
	if (hours < 3.0)
		charge = 2.0;
	else
	{
		charge = 2.0 + 0.5 * ceil(hours - 3.0);
		if (charge > 10)
			charge = 10;
	}
	return charge; 
}