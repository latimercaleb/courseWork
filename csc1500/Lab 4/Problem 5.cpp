// Problem 5 of Lab 4 written by Caleb Latimer
#include<iostream>
#include<fstream>
using namespace std;
void compute(int Atext[][4], int Btext[][4])
{
	int soln[4][4];
	cout << "The join of A and B is \n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			soln[i][j] = Atext[i][j] || Btext[i][j]; // since join is or
			cout << soln[i][j] << " ";
		}
		cout << endl; // Maintain matrix notation 
	}
	cout << "The meet of A and B is \n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			soln[i][j] = Atext[i][j] && Btext[i][j]; // meet is and
			cout << soln[i][j] << " ";	
		}
		cout << endl; 
	}
}
int main()
{
	ifstream Atext,Btext;
	Atext.open("A5.txt");
	Btext.open("B5.txt"); // File read in command to pull in matrix information 
	int Amatrix[4][4];
	int Bmatrix[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Atext >> Amatrix[i][j];
			Btext >> Bmatrix[i][j]; // populates both matrix simultaneously 
		}
	}
	// Test for visibility 
	cout << "My first matrix is \n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << Amatrix[i][j] << " "; // reads out 
		}
		cout << endl; // maintains format 
	}
	cout << "My second matrix is \n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << Bmatrix[i][j] << " "; // reads out 
		}
		cout << endl; // maintains format
	}
	compute(Amatrix,Bmatrix); // Matrix join & meet function for calculating and outputting those methods 
	system("Pause");
}