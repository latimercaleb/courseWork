#include<iostream>
using namespace std;
int main()
{
	int A[11] = { 0 };
	for (int j = 0; j <= 10; j++)
		cin >> A[j];
	for (int j = 0; j <= 10; j++)
		cout << A[j]<< endl;
	return 0;
}