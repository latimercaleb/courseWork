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
	return (pow(n, r));
}
double comb(int n, int r)
{
	return (fact(n+r-1)/(fact(r)*fact(n-1)));
}
int main()
{
	int n, r;
	ifstream A2;
	A2.open("A2.txt");
	if (A2.fail())
	{
		cout << "A2 could not open.\n";
		exit(1);
	}
	ofstream B2;
	B2.open("B2.txt");
	if (B2.fail())
	{
		cout << "B2 could not open.\n";
		exit(1);
	}
	while (A2 >> n >> r)
		B2 << setprecision(0) << fixed << n << " " << r << " " << perm(n, r) << " " << comb(n, r) << endl;
	return 0;
}