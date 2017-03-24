#include<iostream>
using namespace std;
void getData(bool x[], bool y[])
{
	int m,n; 
	bool *soln;
	
	cout << "Enter the length of the first bit string" << endl;
	cin >> m; 
	
	cout << "Enter the length of the second bit string" << endl;
	cin >> n; 
	if (m >= n)
		soln = new bool[m + 1];
	else
		soln = new bool[n + 1];

	cout << "Enter " << m << " values for the first bit string" << endl; 
	for (int i = 0; i < m ; i++)
		cin >> x[i];
	cout << "Enter " << n << " values for the second bit string" << endl;
	for (int j = 0; j < n ; j++)
		cin >> y[j]; // Function for populating bit strings 

	for (int i = (m-1); i >=0; i--)
	{
		static bool z = 0; // carry var
		bool X = x[i];
		bool Y = y[i];

	//		// sum = a xor b xor c 
		soln[i] = ((X ^ Y) ^ z); // change TO BOOL 
	//		// carry = (a &b ) or (b & c) or (a & c)
			z = ((X && Y) || (Y && z) || (X && z));
	}
	cout << "The result is : " << endl;
	for (int i = 0; i < (m-1); i++)
	{
		cout << soln[i] << " ";
	}
	delete[] soln;

} 
//void sum(bool k[], bool w[])
int main()
{
	bool *firstArray;
	bool *secondArray;
	firstArray = new bool[10];
	secondArray = new bool[10];
	getData(firstArray, secondArray);
	//sum(firstArray, secondArray);
}