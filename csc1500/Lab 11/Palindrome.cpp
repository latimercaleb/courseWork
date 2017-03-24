// Lab 11 problem 1 programmed by Caleb Latimer
#include<iostream>
#include<string>
using namespace std;
void palindrome(string);// function prototype takes one parameter of type string
int main()
{
	string input;
	cout << "Enter a string : ";
	getline(cin,input);// used here to take into account spaces entered with the string
	palindrome(input);
	return 0;
}
void palindrome(string first)
{
	bool check = true;// bool to check for the string actually being a palindrome
	string second = first;// initialized second to value to have the same length
	int j = first.length()-1;
	int i;
	for (i = 0; i < first.length(); i++)
	{
		second[i] = first[j]; // forcing second to be the reverse of first string
		j--;
	}
	for (int i = 0; i < first.length(); i++)
	{
		if (first[i] != second[i]) // checks if the characters are different, if they are then it is not a palindrome
		{
			check = false;
			break;
		}
	}
	if (check == true)
		cout << "YES \n";
	else
		cout << "NO \n";
}
