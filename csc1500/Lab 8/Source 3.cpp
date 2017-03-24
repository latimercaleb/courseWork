// Problem three programmed by Caleb Latimer
#include<iostream>
#include<string>
#include <iomanip>
#include<time.h>
#include<cassert>
#include<cstdlib>
using namespace std;
void displayresult(int first, int second, int p)
{
	cout << p << "     "<< first << "           "<< second << endl;
}
int linearcheck(string x)
{
	clock_t start = clock();
	int check = 0;
	int a = x.length();

	for (int i = 0; i < a; i++)
	{
		char temp = x[i];
		for (int j = 0; j < a; j++)
		{
			if (temp == x[i + 1])
			{
				check++;
				break;
			}
		}
		if (check > 0)
			break;

	}
	clock_t end = clock();
	return end;
	/*if (check > 0)
		return false;
		else*/
}
int booleancheck(string x)
{
	clock_t start = clock();
	int check = 0;
	int a = x.length();

	for (int i = 0; i < a; i++)
	{
		char temp = x[i];
		for (int j = 0; j < a; j++)
		{
			if (temp == x[i + 1])
			{
				check++;
				break;
			}
		}
		if (check > 0)
			break;

	}
	 clock_t end = clock();
	 return end;
	/*if (check > 0)
		return false;
	else
		return true;*/
}
//int generateparam() // string sizes are already predetermined
//{
//	int substitute;
//	substitute = rand() % 256; // sets value of the random number to be no higher than 255
//	cout << "This random number is : " << substitute << endl;
//	//srand(time(NULL)); ???
//	return substitute;
//}
string makeString(int x)
{
	string temp = " ";
	for (int i = 0; i < x && i < 256; i++)
	{
		temp = i;
		
	}
	//cout << "The string you made is : " << temp << endl; // line for testing string visibililty
	return temp;
}
int main()
{
	int param1 = 5;
	int param2 = 10;
	int param3 = 20;
	int param4 = 50;
	int param5 = 80;
	int param6 = 100;
	int param7 = 150;
	int param8 = 200;
	int param9 = 256;

	string str1 = makeString(param1);
	int a = linearcheck(str1); int b = booleancheck(str1);
	string str2 = makeString(param2);
	int c = linearcheck(str2); int d = booleancheck(str2);
	string str3 = makeString(param3);
	int e = linearcheck(str3);  int f = booleancheck(str3);
	string str4 = makeString(param4);
	int g = linearcheck(str4); int h = booleancheck(str4);
	string str5 = makeString(param5);
	int i = linearcheck(str5); int j = booleancheck(str5);
	string str6 = makeString(param6);
	int k = linearcheck(str6); int l = booleancheck(str6);
	string str7 = makeString(param7);
	int m = linearcheck(str7); int n = booleancheck(str7);
	string str8 = makeString(param8);
	int o = linearcheck(str8); int p = booleancheck(str8);
	string str9 = makeString(param9);
	int q = linearcheck(str9); int r = booleancheck(str9);

	cout << "n " << setw(12) << setfill(' ') << " Program 1 " << setw(20) << setfill(' ') << " Program 2 \n";// edit table with iomanip
	displayresult(a,b,param1);
	displayresult(c, d, param2);
	displayresult(e, f, param3);
	displayresult(g, h, param4);
	displayresult(i, j, param5);
	displayresult(k, l, param6);
	displayresult(m, n, param7);
	displayresult(o, p, param8);
	displayresult(q, r, param9);



	return 0;
}