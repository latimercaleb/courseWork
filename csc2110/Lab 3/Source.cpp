// Lab 3 programmed by Caleb Latimer 
#include<iostream>
using namespace std;
void Fill_array(double x[], int size);
void Show_array(double y[], int size);
void Reverse_array(double z[], int size); 
int main()
{
	double myArray[10];
	Fill_array(myArray, 10);
	Show_array(myArray, 10);
	Reverse_array(myArray, 10);
}
void Fill_array(double x[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cin >> x[i];
	}

}
void Show_array(double y[], int size)
{
	cout << "Array : \n";
	for (int j = 0; j < size; j++)
		cout << y[j] << " ";
	cout << endl;
}
void Reverse_array(double z[], int size)
{
	cout << "This is your reversed : \n";
	double flip[10];
	double temp;
	for (int i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			temp = z[9];
			flip[i] = temp;
		}
		else
		temp = z[(i-i)+ (9 -i)] ;
		flip[i] = temp;
	}
	Show_array(flip, 10);
}