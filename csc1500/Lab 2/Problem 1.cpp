// Part 1 of problem 1 coded by Caleb Latimer
// 1. Declare two arrays to store two binary numbers with maximum capacity of 10 bits. Assign
//the values of ”0000000010” and ”0000000011” to the arrays.Write a computer program that
//sum these two binary numbers using the arrays.The result should be ”0000000101”.
#include<iostream>
using namespace std;
void sum(bool a[], bool b[]);
// int carry (char a[], char b[]); <- function for carry? 
int main()
{
	/*bool *first, *second;
	*first = new bool[10];
	*second = new bool[10]; -> dynamic attempt 
	first[] = { '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' };*/
	bool a[] = {0,0,0,0,0,0,0,0,1,0};
	bool b[] = {0,0,0,0,0,0,0,0,1,1};
	//char result[] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 }; -> solution of output
	sum(a,b);
	return 0;
}
void sum(bool a[], bool b[])
{
	bool z = 0; // carry var
	bool result[10];
	for (int i = 9; i >= 0; i--){
		bool x = a[i];
		bool y = b[i];
		
		// sum = a xor b xor c 
		result[i] = ((x ^ y )^ z); // change TO BOOL 
		// carry = (a &b ) or (b & c) or (a & c)
		z = ((x && y) || (y && z) || (x && z));
	}
	for (int j = 0; j < 10; j++)
		cout << result[j] << " " << endl; // Outputs result 
}

