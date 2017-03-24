// Problem 1 programmed by Caleb Latimer
#include<iostream>
#include<string>
using namespace std;
void isPalindrome(string x); // palindrome function
int main()
{
	string myString;
	cout << "Enter a string \n";
	cin >> myString;
	isPalindrome(myString);
	return 0; 
}
void isPalindrome(string x)
{
	if (x == string(x.rbegin(), x.rend())) 
		cout << "You entered a palindrome \n";
	else
		cout << x << "did not enter a palindrome \n"; 
	
}