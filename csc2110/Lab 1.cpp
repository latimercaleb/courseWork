// Lab 01 by Caleb Latimer 
#include<iostream>
#include <cmath>
using namespace std;
int main()
{
	double a, b, c, z, y, result, result2;
	cout << "Input the values of a, b and c \n";
	cin >> a >> b >> c;
	z = pow(b, 2);
	y = 4 * a*c;
	if (z - y == 0)
	{
		cout << "You have 2 repeat roots \n";
		b *= (-1);
        result = (b - sqrt((z - y))) / (2 * a);
		result2 = (b + sqrt((z - y))) / (2 * a);
		cout << "They are root 1 : " << result << " and root 2 : " << result2 << endl;
	}

	else if (z - y > 0)
	{
		cout << "You have 2 real roots \n";
		b *= (-1);
		result = (b - sqrt((z - y))) / (2 * a);
		result2 = (b + sqrt((z - y))) / (2 * a);
		cout << "They are root 1 : " << result << " and root 2 : " << result2 << endl;
	}

	else
		cout << "You have 2 complex roots \n";

}