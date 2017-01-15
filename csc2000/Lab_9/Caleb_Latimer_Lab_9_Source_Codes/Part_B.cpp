// Part B programmed by Caleb Latimer

#include <iostream>
using namespace std;

int main()

{
	double grade;


	do {
		
		cout << "Tell me a grade." << endl;
		cin >> grade;
		if (grade < 0 || grade > 100)
			cout << "Invalid grade" << endl;
		else
		{
			cout << "The grade is :" << grade << endl;
			break;
		}


	} while (true);

	
	return 0;
}