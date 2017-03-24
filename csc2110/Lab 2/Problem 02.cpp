#include<iostream>
#include<iomanip>
using namespace std;

void getData();
void taxAmount(double cash, double exempt, double pension, double kids);

int main()
{
	getData();
}
void getData()
{
	char married;
	double kids, income, pension, exempt;
	cout << "Are you married? (y or n) \n";
	cin >> married;
	if (married == 'y')
	{
		exempt = 7000;
		cout << "How many children do you have below age 14? \n";
		cin >> kids;
		cout << "What is the combined salary of you and your spouse? \n";
		cin >> income;
		cout << "What is the percentage of gross income contributed to a pension? \n";
		cin >> pension;
		pension = (pension * income) / 100;
		taxAmount(income, exempt, pension, kids);
	}
	else
	{
		exempt = 4000;
		kids = 0;
		cout << "What is your salary? \n";
		cin >> income;
		cout << "What is the percentage of gross income contributed to a pension? \n";
		cin >> pension;
		pension = (pension * income) / 100;
		taxAmount(income, exempt, pension, kids);
	}
}
void taxAmount(double cash, double exempt, double pension, double kids)
{
	double tax;
	double truecash;
	if (kids = 0)
	{
		if (cash <= 15000)
			truecash = (cash * 0.15);
		else if ((cash >= 15001) || (cash <= 40000))
			truecash = cash - (2250 + (cash * 0.25));
		else if (cash >= 40001)
			truecash = 8460 +(cash * 0.35);

		tax = truecash - (exempt + pension + 1500);
		cout << setprecision(6) << showpoint << tax << endl;
	}
	else
	{

		if (cash <= 15000)
			truecash = (cash * 0.15);
		else if ((cash >= 15001) || (cash <= 40000))
			truecash = cash - (2250 + (cash * 0.25));
		else if (cash >= 40001)
			truecash = 8460 + (cash * 0.35);

		tax = truecash - (exempt + pension + (kids * 1500));
		cout<< setprecision(6)<< showpoint << tax << endl;
	}
}