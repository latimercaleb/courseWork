// Problem two programmed by Caleb Latimer
#include<iostream>
#include<string>
using namespace std;
bool checkString(string x)
{
	bool testarray[256];
	for (int i = 0; i < 256; i++)
		testarray[i] = false;
	int a = x.length();
	char point;
	int testsearch;
	for (int i = 0; i < a; i++)
	{
		point = x[i];
		testsearch = static_cast<int>(point);
		if (testarray[testsearch] == false) 
		{
			testarray[testsearch] = true;
		}
		else
		{
			return false;
			break;
		}

	}
	return true;

}
int main()
{
	string entry;
	cout << "Enter a string without spaces :";
	cin >> entry;
	bool sln = checkString(entry);
	if (sln == true)
		cout << "No duplicate uniques were found \n";
	else
		cout << "Unique duplicates\n";
	
}