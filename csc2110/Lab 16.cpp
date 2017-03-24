// Lab 16 written by Caleb Latimer
#include<iostream>
using namespace std;

template<class baz>
void sort(baz test[], int size)

{
	
	int temp;
	try
	{
		if (size < 5)
			throw size;
		for (int i = 1; i < size; i++)
		{
			for (int j = 0; j < (size-1); j++)
			{
				if (test[j] > test[j+1])
				{
					temp = test[j];
					test[j] = test[j+1];
					test[j+1] = temp;
				}
			}
		}
		cout << "The sorted new array is : ";
		for (int i = 0; i < size; i++)
			cout << test[i] << " ";
		cout << endl;
	}
	catch (int x)
	{
		cout << "Size is too small to sort\n";
	}
	
}
int main()
{
	int myArray[7] = { 9, 8, 7, 6, 5,4,3 };
	sort(myArray, 7);

	double myOtherArray[7] = { 9, 8, 7, 6, 5, 34, 16 };
	sort(myOtherArray, 7);

	int myLastArray[4] = { 2, 16, 8, 7 };
	sort(myLastArray, 4);

	return 0; 
}