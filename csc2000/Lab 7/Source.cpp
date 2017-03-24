// Lab 8 programmed by Caleb Latimer

#include <iostream>
using namespace std;

int main()
{
	int num, unit, ans;
	cout << "Tell me an integer\n";
	cin >>  num;
	

	do {
		unit = num % 10;
		cout << unit;
		 num = num/10;
		
		

	} while (num != 0);
	cout << endl;

	
	return 0;
}