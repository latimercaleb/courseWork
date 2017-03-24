// Part D programmed by Caleb Latimer

#include <iostream>
using namespace std;

int main()

{
	double grade;
	int i = 0;
	
	do {

		cout << "Tell me a grade." << endl;
		cin >> grade;

		if (grade == 999)
			break;
		else if (grade < 0 || grade > 100)
		{
			cout << "Invalid grade" << endl;
			i++;
			if (i == 5)
				break;
		}

		else
		{
			cout << "The grade is :" << grade << endl;
			break;
		}
	} while (true);

	}
	
