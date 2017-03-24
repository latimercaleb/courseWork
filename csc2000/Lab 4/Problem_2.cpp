// Lab 5 Problem 2 Programmed by Caleb Latimer

#include <iostream>
using namespace std;

int main()
{
	int a, b, c;
	cout << "Tell me three numbers" << endl;
	cin >> a >> b >> c; 

	if (a <= c && b <= c)
	{
		if (a <= b)
			cout << "In Ascending order : " << a << " " << b << " " << c << endl;
		if (b <= a)
			cout << "In Ascending order : " << b << " " << a << " " << c << endl;
	}
	else if (c <= a && b <= a)
	{
		if (c <= b)
			cout << "In Ascending order : " << c << " " << b << " " << a << endl;
		if (b <= c)
			cout << "In Ascending order : " << b << " " << c << " " << a << endl;
	}
	else if (a <= b && c <= b)
	{
		if (a <= c)
			cout << "In Ascending order : " << a << " " << c << " " << b << endl;
		if (c <= a)
			cout << "In Ascending order : " << c << " " << a << " " << b << endl;
	}
	else
		cout << "In Ascending order : " << a << " " << b << " " << c << endl;
	return 0;
}