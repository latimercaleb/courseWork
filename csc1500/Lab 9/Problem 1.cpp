// Problem 1 programmed by Caleb Latimer
#include<iostream>
#include<string> // needed to handle string inputs
using namespace std;
//const char alpha[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char encrypt(char); // function of encrypting 
int main()
{
	string input, encrypted;
	cout << "Enter a string : ";
	cin >> input;
	for (int i = 0; i < input.length(); i++)// for loop to call function and build result
		encrypted += (encrypt(input[i])); // sets each character of the new string to what the functions returns
	cout << encrypted << endl; // prints result
	return 0;
}

char encrypt(char letter) 
{
	if (isalpha(letter)) // checks if the character entered is alphabetical or not
	{
		letter = toupper(letter); // brings it to upper case
		letter = ((((letter -65) + 2) % 26 )+65); // subtract 65 then add it back to remove all other ascii characters other thant the upper case letter set. 
	} // 2 is hardcoded in as the key for this program as per the assumption in the description 
	return letter;
}
// tested on test values provided, code works successfully
