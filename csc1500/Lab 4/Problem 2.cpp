// Problem 2 of Lab 4 programmed by Caleb Latimer
// Email to Adib 
#include<iostream>
#include<fstream>
//#include<Eigen/Dense> nope doesn't help 
using namespace std;
bool isittri(int myArray[][4])
{
	bool check = false;
	//bool trap = true;

	for (int i = 0; i < 4; i++)// selects row
	{
		check = false; // check starts out false 
		for (int j = 0; j < 4; j++) // selects column
		{
			if ((myArray[i] > myArray[j] && myArray[i][j] == 0)){// checks if below diagnol is 0
				// Fix logic of this statement ?
				check = true;
			}
			//check = false; -> cannot insert code between an if/else
			else if ((myArray[i] < myArray[j]) && myArray[i][j] == 1){ // checks if above diagnol is 1 or greater
					check = true;
					//break;
				}
				//check = false;
			else if ((myArray[i] == myArray[j]) && myArray[i][j] == 1){// checks if the diagnol is 1 or greater
					check = true;
				} // This loop runs and checks each value in the row for upper triangle and returns true if all parts pass
				//cout << myArray[i][j] << " ";
			else{
				check = false;
			}
			//cout << endl;
			if (check == false) // if any of j fails then check will still be false which will break the loop and declare not an upper triangle
				break;// THIS WAS MY PROBLEM! Without it inside of the interior it took the last value instead of the row! 
		}
		if (check == false) // if any of j fails then check will still be false which will break the loop and declare not an upper triangle
			break;

	}
	if (check == true)
		return true;
	else
		return false;
	//return true;
}
int main()
{
	ifstream A2;
	A2.open("A2.txt");
	bool bar = false;
	int myArray[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			A2 >> myArray[i][j];
			//cout << darray[i][j]; //checking for data to read in 
		}
		//cout << endl;
	}
	bar = isittri(myArray);
	if (bar == true)
		cout << "The 4x4 matrix is an upper triangular\n";
	else
		cout << "The 4x4 matrix is not an upper triangular \n";
}