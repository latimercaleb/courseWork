// Problem one programmed by Caleb Latimer
// test value used was the string taco and taaco with these values it works properly 
#include<iostream>
#include<string>
using namespace std;
bool checkString(string x)
{
	int check = 0;
	int a = x.length();

	for (int i = 0; i < a; i++)
	{
		char temp = x[i];
		for (int j = 0; j < a; j++)
		{
			if (temp == x[i+1])
			{
				check++;
				break;
			}
		}
		if (check > 0)
			break;

	}
	if (check > 0)
		return false;
	else
		return true;
}
int main()
{
	string entry;
	cout << "Enter a string without spaces :";
	cin >> entry;

	bool z = checkString(entry);
	if (z == false)
		cout << "Duplicate unique characters detected.\n";
	else
		cout << "No copies\n";
}