// By Caleb Latimer
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
int binsearch(int x[], int y, int a, int b)
{
	int partition = (a+b) / 2;
	if (b < a)
		return -1;
	else
	{
		if (x[partition] == y)
			return partition;
		else if (x[partition] < y)
			return binsearch(x,  y, partition+1,  b);
		else
			return binsearch(x, y, a, partition-1  );
	}
}
int main(){
	int myNum[15];
	int index = 0;
	ifstream A3;
	A3.open("A3.txt");
	if (A3.fail())
	{
		cout << "A3 failed\n";
		exit(1);
	}
	ofstream B3;
	B3.open("B3.txt");
	if (B3.fail())
	{
		cout << "B3 failed\n";
		exit(1);
	}

	int check = 0;
	while (!A3.eof())
	{
		A3 >> check;
		for (int i = 0; i < 15; i++)
			A3 >> myNum[i];
		index = binsearch (myNum, check, 0, 14);
		if (index == -1)
			B3 << "Not found\n";
		else
			B3 << "The index of the number is : " << index << endl;


	}
	
}