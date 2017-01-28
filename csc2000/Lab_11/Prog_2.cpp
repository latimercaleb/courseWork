// Lab_11 problem 2 progged by Caleb Latimer
#include<iostream>
using namespace std;

void getData(double& price, double& oldPrice, double& xoldPrice);
void inflationCalculate(double& price, double& oldPrice, double& xoldPrice);
void viewResult(double& inflation, double& inflation2x);

int main()
{
	double price, oldPrice, xoldPrice, inflation, inflation2x;

	getData(price, oldPrice, xoldPrice);
	inflationCalculate(price, oldPrice, xoldPrice);
	viewResult(inflation, inflation2x);
	
}



void getData(double& price, double& oldPrice, double& xoldPrice)
{
	cout << "Enter the current price of the item: ";
	cin >> price;
	cout << endl;
	cout << "Enter the price of the item one year ago: ";
	cin >> oldPrice;
	cout << endl;
	cout << "Enter the price of the item two years ago: ";
	cin >> xoldPrice;
	cout << endl;
}


void inflationCalculate(double& price, double& oldPrice, double& xoldPrice)
{
	double inflation, inflation2x;
	inflation = (oldPrice - price) / oldPrice;
	cout << "Current year inflation: " << inflation << endl;
	inflation2x = (xoldPrice - price) / xoldPrice;
	cout << "Inflation one year ago: " << inflation2x << endl;

}

void viewResult(double& inflation, double& inflation2x)
{
	if (inflation > inflation2x)
		cout << "Inflation is decreasing." << endl;
	else if (inflation < inflation2x)
		cout << "The inflation is increasing." << endl;
	else
		cout << "No change in inflation." << endl;
}