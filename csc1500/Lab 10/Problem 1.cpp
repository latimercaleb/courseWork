//Lab 10 programmed by Caleb Latimer
// Had to use doubles as return types ints returned the wrong output
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
using namespace std;
double fact(int n)
{
	if (n == 1)
		return 1;
	else if (n == 0)
		return 1;
	else
		return n * fact(n - 1);
}
double perm(int n, int r)
{
	return (fact(n) / fact(n - r));
}
double comb(int n, int r)
{
	return (fact(n) / (fact(n - r)*fact(r)));
}
int main()
{
	int n, r;
	ifstream A1;
	A1.open("A1.txt");
	if (A1.fail())
	{
		cout << "A1 could not open.\n";
		exit(1);
	}
	ofstream B1;
	B1.open("B1.txt");
	if (B1.fail())
	{
		cout<< "B1 could not open.\n";
		exit(1);
	}

	while (A1 >> n >> r)
	{
		if (r > n)
			B1 << n << " "<< r << " "<< "r>n error" << endl;
		else
		{
			B1 << setprecision(0) << fixed << n << " " << r << " " << perm(n, r) << " " << comb(n, r) << endl;
		}
	}
}