// lab 20 written by Caleb Latimer 
#include<iostream>
using namespace std;
void bubble( int arr[],int &size)
{    
	int temp;  
	bool check = true;
	for (int i = 1; (i < size) && (check); i++)
	{
		
		check = false;
		for (int j = 0; j < (size - i) ; j++)
			{
				if (arr[j + 1] < arr[j])
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
					check = true;
				}
			}
		
	}
	return;   
}
int main()
{
	int list[] = {9,7,4,1,8,5,3,9,2};
	int size = 9;
	cout << "Unsorted \n";
	for (int i = 0; i < size; i++)
		cout << list[i] << " ";
		cout << endl;
		cout << "Sorted\n";
	bubble(list, size);
	for (int i = 0; i < size; i++)
		cout << list[i] << " ";
	cout << endl;
	return 0;
}