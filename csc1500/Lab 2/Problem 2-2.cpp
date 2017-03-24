// Problem 2-2 of lab 2 by Caleb Latimer
#include<iostream>
using namespace std;
void intersection(char first[], char second[])
{
	int dif = 0;
	//int error = 0;
	char myNew[20];
	for (int j = 0; j < 19; j++)
	{
		if (first[j + 2] == second[j])
			myNew[j] = first[j + 2];
	}


	cout << "My intersection of the set is : ";
	for (int k = 0; k < 19; k++)
	{
		if (myNew[k] != NULL)
			cout << myNew[k] << ", ";
		else
			cout << NULL << ", ";
	}

}
int main()
{
	char myFirst[20] = { 'A', 'B', 'C', 'D' };
	/*for (int i = 0; i < 20; i++)
	cout << myFirst[i] << " , ";*/
	char mySecond[20] = { 'C', 'D', 'E' };
	intersection(myFirst, mySecond);
	return 0;
}