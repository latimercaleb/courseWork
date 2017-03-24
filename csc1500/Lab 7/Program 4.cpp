// By Caleb Latimer
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

void combine(int a[], int p, int mid, int r)
{
	ofstream B4;
	B4.open("B4.txt");
	if (B4.fail())
	{
		cout << "B4 failed to open\n";
		exit(1);
	}
	
	int *store = new int[15];
	int left, num, temp;
	left = mid - 1;
	temp = p;
	num = (r - p + 1);

	while ((left <= p) && (mid <= r))
	{
		if (a[left] < a[mid])
		{
			store[temp] = a[left];
			temp++;
			left++;
		}
		else
		{
			store[temp] = a[mid];
			temp++;
			mid++;
		}
	}

	while (left <=p)
	{
		store[temp] = a[mid];
		left++;
		temp++;
	}
	while (mid <= r)
	{
		store[temp] = a[mid];
		mid++;
		temp++;
	}
	for (int i = 0; i <= num; i++) 
	{
		a[r] = store[r];
		r--;
	}
	for (int i = 0; i < 15; i++)
		B4 << store[i] << " ";
	
}
void mergeSort(int x[], int p, int r)
{
	int mid = (p + r) / 2;
	if (p < r) {
		
		mergeSort(x, p, mid);
		mergeSort(x, (mid + 1), r);
	}
	return combine(x, p, mid, r);
}
int main(){
	int myNum[15];
	ifstream A4;
	A4.open("A4.txt");
	if (A4.fail())
	{
		cout << "A4 failed to open\n";
		exit(1);
	}
	
	while (!A4.eof())
	{
		for (int i = 0; i < 15; i++)
			A4 >> myNum[i];
		mergeSort(myNum,0,14);
		
	}
}