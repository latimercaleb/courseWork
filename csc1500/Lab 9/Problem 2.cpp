// Problem 2 programmed by Caleb Latimer
#include<iostream>
#include<string> // needed to handle string inputs
using namespace std;
char decrypt(char); // decrypting function
int main() {
	cout << "Input an encrypted string: ";
	string encrypted, decrypted;
	cin >> encrypted;
	for (int i = 0; i < encrypted.length(); i++)
		decrypted += decrypt(encrypted[i]); // sets each character in the result to what the function returns
	
	cout << "The decrypted text is " << decrypted << endl; // prints result
	return 0; 
}
char decrypt(char in)
{
	if (isalpha(in)) // check if character is alphabet
	{
		in = toupper(in); // brings it to upper case
		in = (((in - 2)-65) % 26)+65; // does the 65 char restriction to only get upper case alphabet letters
	}

	return in;
}
// tested on the same test value from the example, code works successfully