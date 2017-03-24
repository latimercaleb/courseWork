// By Caleb Latimer
#include<iostream>
#include<fstream>
using namespace std;
void bubbleSort(int c[], int first, int last)
{
	ofstream B2;
	B2.open("B2.txt");
	if (B2.fail())
	{
		cout << "B2 did not open";
		exit(1);
	}

	int i = 0;
	if (c[first] < c[last] && c[last] > 0) 
	{
		if (c[first] > c[first + 1]) 
		{
			int temp = c[first];
			c[first] = c[first + 1];
			c[first + 1] = temp;
		}
		bubbleSort(c, (first + 1), last);
		bubbleSort(c, first, (last - 1));
	}
	else {
		 
			B2 << c[last] << " ";
			cout << c[last] << " ";
			
		return;
	}
}
int main(){
	int store[15];

	ifstream A2;
	A2.open("A2.txt");
	if (A2.fail())
	{
		cout << "A2 did not open";
		exit(1);
	}

	int row = 0; 
	while (row < 10)
	{
		for (int i = 0; i < 15; i++)
			A2 >> store[i];
		bubbleSort(store, 0, 14);
		row++;
	}
}