// Problem 2 of Lab 4 programmed by Caleb Latimer
#include<iostream>
using namespace std;
//int initializeAB(int[][], int[][]);
void sumAB(int A[][3], int B[][3]);
int main()
{
	int A[2][3] = { { 1, 1, 1 }, { 1, 1, 1 } };
	int B[2][3] = { { 2, 2, 2 }, { 2, 2, 2 } };
	//initializeAB();
	sumAB(A,B);// need forloop
	return 0; 
}
//int initializeAB(int[][], int[][])
void sumAB(int A[2][3], int B[2][3])
{
	int sum[2][3];
	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 3; j++)
		sum[i][j] = (A[i][j] + B[i][j]);

	for (int i = 0; i < 2; i++)
	{
		cout << sum[i][0] << endl;
		for (int j = 1; j < 3; j++)
		{
			cout << sum[i][j] << endl;
		}
		cout << endl; 
	}
}