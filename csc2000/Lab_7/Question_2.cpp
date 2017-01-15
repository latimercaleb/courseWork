// Lab 7 Question 2 programmed by Caleb Latimer


#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int  g;
	double meter, feet, numCon, increment;

	cout << "Enter the number of meters, conversions and increments" << endl;
	cin >> meter >> numCon >> increment;

	if (numCon > 10)
	{
		increment = 10;
	}
		
		for (g = 0; g < numCon; g++)
		{
			feet = meter * 3.281;
			cout << "Feet" << ' ' << setw(10) << "Meters" << endl;
			cout << feet << ' ' << setw(5) << meter << endl;
			meter = meter + increment; 
			

		}
	
	

	return 0;
}
