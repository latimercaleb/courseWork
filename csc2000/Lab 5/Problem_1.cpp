// Lab 6 problem 1 programmed by Caleb Latimer

#include <iostream>
using namespace std;

int main()
{
	char  degree;
	double temp , nextTemp;

	cout << "Hello, give me a temp in degree fahrenheit or celsius.\n";
	cin >> temp >> degree;

	if (degree == 'c' || degree == 'C')
	{

		nextTemp = (9.0 / 5.0) * (temp) + 32.0;
		cout << "The conversion to Fahreinheit yields : " << nextTemp << "F."<< endl;
	}
	else if (degree == 'f' || degree == 'F')
	{
		
		nextTemp = (5.0 / 9.0) * (temp - 32.0);
		cout << " The conversion to Celsius yields : " << nextTemp << "C." << endl;
	}
	else
		
		cout << "Invalid data, terminating program \n";

	return 0;
}