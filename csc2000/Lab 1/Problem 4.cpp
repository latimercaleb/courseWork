#include <iostream>
using namespace std;

int main()
{
	int a = 5, b = 6, c;
	a = (b++) + 3;
	cout << a << endl;
	cout << b << endl;
	//cout << c << endl; 

	c = 2 * a + (++b);
	cout << a << endl;
	cout << b << endl;
	cout << c << endl; 

	b = 2 * (++c) - (a++);
	cout << a << endl;
	cout << b << endl;
	cout << c << endl; 

	return 0;
}