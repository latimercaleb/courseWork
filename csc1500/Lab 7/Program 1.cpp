// By Caleb Latimer
// Please refer to my A1.txt file attached in the zip since I removed the whitespace at the end of the line 
#include<iostream>
#include<fstream>
#include <cstdlib>
using namespace std;
int gcd(int, int);

int main(){
	ifstream A1;
	A1.open("A1.txt");
	if (A1.fail())
	{
		cout << "File failed to open for some reason\n";
		exit(1);
	}

	ofstream B1;
	B1.open("B1.txt");
	if (B1.fail())
	{
		cout << "File failed to open for some reason. \n";
		exit(1);
	}

	int x =0, y =0, z =0;

	while (A1 >> x >> y)
	{
		
		if (A1.get() == '\n')
		{
			B1 << gcd(x, y) << " ";
		}

		else
		{
			A1 >> z;
			B1 << gcd(x, (gcd(y,z))) << " ";
			
		}
	}
	return 0;
}
int gcd(int a, int b)
{
	
	if (b == 0)
		return a;
	else
		gcd(b, a % b);
}
