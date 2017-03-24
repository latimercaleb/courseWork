// Anagram problem 2 lab 11 by Caleb Latimer
#include<iostream>
#include<string>
using namespace std;
string sort(string&);
void anagram(string,string);
int main()
{
	string input1,input2;
	cout << "Enter the first string wihtout spaces : ";
	cin >> input1;
	cout << "Enter the second string without spaces : ";
	cin >> input2;
	anagram(input1,input2);
	return 0;
}
string sort(string &input)// bubble sort to inputs changing the characters in the string by ascii value from lowest to highest
{
	for (unsigned int i = 1; i < input.length(); i++)
	{
		for (unsigned int j = 0; j < input.length()-1; j++)
		{
			if (input[j+1] < input[j])
				swap(input[j], input[j+1]);
		}
	}
	return input;
}

void anagram(string first, string second)
{
	if (first.length() == second.length()) // only executes if the two strings are equal 
	{
		bool check = true;
		sort(first);
		sort(second); // sorts strings
		for (unsigned int i = 0; i < first.length(); i++)
		{
			if (first[i] != second[i])// checks for non-identical characters, if any of them are different then the second is not an anagram of the first
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
	else
		cout << "The strings are not of the same length, therefore they are not anagrams \n";
}

