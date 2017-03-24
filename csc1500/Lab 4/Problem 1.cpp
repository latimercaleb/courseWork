// Problem 1 of Lab 4 programmed by Caleb Latimer 
#include<iostream>
//#include <vector>
using namespace std;
void matrix(int z)
{
	//vector<int> myMatrix(z); Got stuck trying to use 2D arrays and couldn't use vectors either
	//vector<int>  my2Matrix(z);
	for (int i = 0; i < z; i++) // Nested loop checks conditions for matrix and then prints matrix directly
	{
		for (int j = 0; j < z; j++)
		{
			if (i == j){
				cout << 1;
			}
			////else if (i > j){
			//	myMatrix.push_back(0);
			//	my2Matrix.push_back(0);
			//}
			else{
				cout << 0; 
			}

			//cout << myMatrix[i] << " " << my2Matrix[j]; 
		}
		cout << endl;
	}


}
int main()
{

	int z; 
	cout << "Input some integer : ";
	cin >> z;
	while (z <= 1)
	{
		cout << "Invalid input put in a number greater than 1 : ";
		cin >> z;
	}
	matrix(z);
	return 0; 
}